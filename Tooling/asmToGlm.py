import sys
import shlex

template_mul = "{} = {} * {};"
template_add = "{} = {} + {};"

tempVarCounter = 0




def CreateTemp():
    global tempVarCounter
    makeName = "temp_{}".format(tempVarCounter)
    tempVarCounter += 1
    return makeName


iTrue = CreateTemp()
iFalse = CreateTemp()

iRV0 = CreateTemp()
iRV1 = CreateTemp()

iTempList = [
    CreateTemp(),
    CreateTemp(),
    CreateTemp(),
    CreateTemp()
]

uTempList = [
    CreateTemp(),
    CreateTemp(),
    CreateTemp(),
    CreateTemp()
]

fTempList = [
    CreateTemp(),
    CreateTemp(),
    CreateTemp(),
    CreateTemp()
]







def HardCastToF32(x):
    return "(*reinterpret_cast<float*>(&{}))".format(x)

def HardCastToI32(x):
    return "(*reinterpret_cast<int32_t*>(&{}))".format(x)

def HardCastToU32(x):
    return "(*reinterpret_cast<uint32_t*>(&{}))".format(x)



def AsIntFunc(x, i):
    return "AsInt({})".format(x) if i else x

def shlexsplit(x):
    spl = shlex.shlex(x, posix=True)
    spl.whitespace += ','
    spl.whitespace_split = True
    return list(spl)

swizzleIndex = {
    "x" : 0,
    "y" : 1,
    "z" : 2,
    "w" : 3
}

def CppVec(x, a):
    if x == 0 or x == 1:
        return a
    else:
        return "vec{}({})".format(x, a)


def LiteralCheck(x):
    if x.startswith("_CONVERT"):
        # Remove Convert
        a = x.replace(")", "")
        a = a.replace("_CONVERT(", "")
        
        vecType = len(shlexsplit(a))
        return CppVec(vecType, a)
    else:
        return x

def NegativeCheck(x):
    if x.startswith("-"):
        t = x.split(".")
        if len(t) == 1:
            return x
        
        swizzleLength = len([1])
        return "-" + CppVec(swizzleLength, x[1:])
    else:
        return x

def AbsCheck(x):
    if x.startswith("|"):
        swizzleLength = len(x[1:-1].split(".")[1])
        return "abs({})".format(CppVec(swizzleLength, x[1:-1]))
    else:
        return x

def Sane(x, sl):
    x = LiteralCheck(x)
    x = NegativeCheck(x)
    x = AbsCheck(x)
    return x

def Dstify(x):
    swizzleLength = len(x.split(".")[1])
    return x, swizzleLength





def GetSwizzle(x, inde):
    return x.split(".")[1][inde]

def GetMaskAndIndex(x, inde):
    a = GetSwizzle(x, inde)
    return a, swizzleIndex[a]

def GetSwizzleIndices(x, l):
    indx = []
    for i in range(l):
        a = GetSwizzle(x, i)
        indx.append(swizzleIndex[a])

    return indx

def CreateVectorFromSrc(src, indxs):
    vecLen = len(indxs)
    Negative = False

    if src.startswith("_CONVERT"):
        # LITERAL
        rx = shlexsplit(src[9:-1].replace(" ",""))
    
        nrx = []

        for i in rx:
            nrx.append(i + (".f" if len(i.split(".")) == 1 else "f"))

        rx = nrx

        if len(rx) < 2:
            # has a point
            return ''.join(rx)

        return CppVec(vecLen, ','.join([rx[i] for i in indxs]))

    if vecLen == 1:
        if src.startswith("|"):
            return "abs({})".format(src[1:-1])
        return src

    ## Handle Negative
    if src.startswith("-"):
        Negative = True
        src = src[1:]

    ## Handle vectors
    vecStart = src.split(".")[0]
    vecExt = src.split(".")[1]
    vecExt = [vecExt[i] for i in indxs]


    if src.startswith("|"):
        vecStart = vecStart[1:]
        return "abs({})".format(("-" if Negative else "") + 
            CppVec(vecLen, vecStart + "." + ''.join(vecExt)))
        

    return ("-" if Negative else "") + CppVec(vecLen, vecStart + "." + ''.join(vecExt))

def GetNamedSwizzle(x, inde):
    if x.startswith("_CONVERT"):
        # LITERAL
        rx = shlexsplit(x[9:-1].replace(" ",""))
    
        nrx = []

        for i in rx:
            nrx.append(i + (".f" if len(i.split(".")) == 1 else "f"))

        rx = nrx

        if len(rx) < 2:
            # has a point
            return ''.join(rx)

        return rx[inde]
    elif x.startswith("|"):
        x = x[1:-1]

        if len(x.split(".")[1]) < 2:
            return ''.join(x)

        a = GetSwizzle(x, inde)
        return "abs({})".format(x.split(".")[0] + "." + a)
    else:
        a, sl = Dstify(x)

        if sl < 2:
            return a

        a = GetSwizzle(a, inde)
        return x.split(".")[0] + "." + a

def DIV(xs):
    """Float to float"""
    dst, sl = Dstify(xs[0])
    src0 = xs[1]
    src1 = xs[2]

    indices = GetSwizzleIndices(dst, sl)
    src0 = CreateVectorFromSrc(src0, indices)
    src1 = CreateVectorFromSrc(src1, indices)

    print("{} = {} / {};".format(dst, src0, src1))

    # for i in range(sl):
    #     s, m = GetMaskAndIndex(dst, i)
    #     print("{} = {} / {};".format(
    #         GetNamedSwizzle(dst, i),
    #         GetNamedSwizzle(src0, m),
    #         GetNamedSwizzle(src1, m)
    # ))

def DIVSAT(xs):
    """float to float"""
    dst, sl = Dstify(xs[0])
    src0 = xs[1]
    src1 = xs[2]

    for i in range(sl):
        s, m = GetMaskAndIndex(dst, i)
        print("{} = min(1.f, max(0.f, {} / {}));".format(
            GetNamedSwizzle(dst, i),
            GetNamedSwizzle(src0, m),
            GetNamedSwizzle(src1, m)
    ))

def ADDSAT(xs):
    """float to float"""
    dst, sl = Dstify(xs[0])
    src0 = xs[1]
    src1 = xs[2]

    indices = GetSwizzleIndices(dst, sl)
    src0 = CreateVectorFromSrc(src0, indices)
    src1 = CreateVectorFromSrc(src1, indices)

    print("{} = min(1.f, max(0.f, {} + {}));".format(dst, src0, src1))

    # for i in range(sl):
    #     s, m = GetMaskAndIndex(dst, i)
    #     print("{} = min(1.f, max(0.f, {} + {}));".format(
    #         GetNamedSwizzle(dst, i),
    #         GetNamedSwizzle(src0, m),
    #         GetNamedSwizzle(src1, m)
    # ))

def LOG(xs):
    """float to float"""
    dst, sl = Dstify(xs[0])
    src0 = xs[1]

    for i in range(sl):
        s, m = GetMaskAndIndex(dst, i)
        print("{} = log({});".format(
            GetNamedSwizzle(dst, i),
            GetNamedSwizzle(src0, m)
    ))

def EXP(xs):
    """float to float"""
    dst, sl = Dstify(xs[0])
    src0 = xs[1]

    for i in range(sl):
        s, m = GetMaskAndIndex(dst, i)
        print("{} = exp({});".format(
            GetNamedSwizzle(dst, i),
            GetNamedSwizzle(src0, m)
    ))

def CEIL(xs):
    """float to float"""
    dst, sl = Dstify(xs[0])
    src0 = xs[1]

    for i in range(sl):
        s, m = GetMaskAndIndex(dst, i)
        print("{} = ceil({});".format(
            GetNamedSwizzle(dst, i),
            GetNamedSwizzle(src0, m)
    ))

def FLOOR(xs):
    """float to float"""
    dst, sl = Dstify(xs[0])
    src0 = xs[1]

    for i in range(sl):
        s, m = GetMaskAndIndex(dst, i)
        print("{} = floor({});".format(
            GetNamedSwizzle(dst, i),
            GetNamedSwizzle(src0, m)
    ))

def ROUND_TO_ZERO(xs):
    """float to float"""
    dst, sl = Dstify(xs[0])
    src0 = xs[1]

    for i in range(sl):
        s, m = GetMaskAndIndex(dst, i)
        print("{} = door({});".format(
            GetNamedSwizzle(dst, i),
            GetNamedSwizzle(src0, m)
    ))

def CEILSAT(xs):
    """float to float"""
    dst, sl = Dstify(xs[0])
    src0 = xs[1]

    for i in range(sl):
        s, m = GetMaskAndIndex(dst, i)
        print("{} = min(1.f, max(0.f, ceil({})));".format(
            GetNamedSwizzle(dst, i),
            GetNamedSwizzle(src0, m)
    ))

def MUL(xs):
    dst, sl = Dstify(xs[0])
    src0 = xs[1]
    src1 = xs[2]

    indices = GetSwizzleIndices(dst, sl)
    src0 = CreateVectorFromSrc(src0, indices)
    src1 = CreateVectorFromSrc(src1, indices)

    print(template_mul.format(dst, src0, src1))

    # for i in range(sl):
    #     s, m = GetMaskAndIndex(dst, i)
    #     print("{} = {} * {};".format(
    #         GetNamedSwizzle(dst, i),
    #         GetNamedSwizzle(src0, m),
    #         GetNamedSwizzle(src1, m)
    # ))

def FMA(xs):
    dst, sl = Dstify(xs[0])
    src0 = xs[1]
    src1 = xs[2]
    src2 = xs[3]

    indices = GetSwizzleIndices(dst, sl)
    src0 = CreateVectorFromSrc(src0, indices)
    src1 = CreateVectorFromSrc(src1, indices)
    src2 = CreateVectorFromSrc(src2, indices)

    print("{} = {} * {} + {};".format(dst, src0, src1, src2))

    # for i in range(sl):
    #     s, m = GetMaskAndIndex(dst, i)
    #     print("{} = {} * {} + {};".format(
    #         GetNamedSwizzle(dst, i),
    #         GetNamedSwizzle(src0, m),
    #         GetNamedSwizzle(src1, m),
    #         GetNamedSwizzle(src2, m)
    # ))

    # dst, sl = Dstify(xs[0])
    # src0 = Sane(xs[1], sl)
    # src1 = Sane(xs[2], sl)

    # print(template_mul.format(dst, src0, src1))



def ADD(xs, Integer=False):
    # dst, sl = Dstify(xs[0])
    # src0 = Sane(xs[1], sl)
    # src1 = Sane(xs[2], sl)

#    Integer = False # Reset this

    # print(template_add.format(dst, src0, src1))
 #   Registers = 0    

    dst, sl = Dstify(xs[0])
    src0 = xs[1]
    src1 = xs[2]



    if not Integer:
        indices = GetSwizzleIndices(dst, sl)
        src0 = CreateVectorFromSrc(src0, indices)
        src1 = CreateVectorFromSrc(src1, indices)

        print("{} = {} + {};".format(dst, src0, src1))
    else:
        # Temps
        for i in range(sl):
            s, m = GetMaskAndIndex(dst, i)
            #rv1 = CreateTemp()
            #rv2 = CreateTemp()

            src0rv1 = GetNamedSwizzle(src0, m)
            src1rv2 = GetNamedSwizzle(src1, m)

            print("{} = {} + {}".format(
                iTempList[i],
                HardCastToI32(src0rv1),
                HardCastToI32(src1rv2),
            ))

            #print("uint32_t {} = {};".format(rv1, HardCastToI32(src0rv1)))
            #print("uint32_t {} = {};".format(rv2, src1rv2))
            #print("{} = {} + {};".format(dst, HardCastToI32(rv1), HardCastToI32(rv2)))
            
        for i in range(sl):
        #    s, m = GetMaskAndIndex(dst, i)
            
            print("{} = {};".format(
                GetNamedSwizzle(dst, i),
                HardCastToF32(iTempList[i])
            ))

        





def SINCOS(xs):
    dst0, sl0 = Dstify(xs[0])
    dst1, sl1 = Dstify(xs[1])
    src = Sane(xs[2], sl0)

    print("{} = sin({});".format(dst0, CppVec(sl0, src)))
    print("{} = cos({});".format(dst1, CppVec(sl1, src)))

def MOV(xs):
    # dst, sl = Dstify(xs[0])
    # src0 = Sane(xs[1], sl)

    # print("{} = {};".format(dst, src0))

    dst, sl = Dstify(xs[0])
    src0 = xs[1]

    indices = GetSwizzleIndices(dst, sl)
    src0 = CreateVectorFromSrc(src0, indices)
    #src1 = CreateVectorFromSrc(src1, indices)
    #src2 = CreateVectorFromSrc(src2, indices)

    print("{} = {};".format(dst, src0))

    # for i in range(sl):
    #     s, m = GetMaskAndIndex(dst, i)
    #     print("{} = {};".format(
    #         GetNamedSwizzle(dst, i),
    #         GetNamedSwizzle(src0, m)
    #     ))

def LT(xs):
    # dst, sl = Dstify(xs[0])
    # src0 = Sane(xs[1], sl)
    # src1 = Sane(xs[2], sl)

    # print("{} = {} < {};".format(dst, src0, src1))

    dst, sl = Dstify(xs[0])
    src0 = xs[1]
    src1 = xs[2]

    # indices = GetSwizzleIndices(dst, sl)
    # src0 = CreateVectorFromSrc(src0, indices)
    # src1 = CreateVectorFromSrc(src1, indices)

    #print("{} = {} < {};".format(dst, src0, src1))
    print("{")
    for i in range(sl):
        s, m = GetMaskAndIndex(dst, i)
        #rv1 = CreateTemp()
        #rv2 = CreateTemp()

        src0rv1 = GetNamedSwizzle(src0, m)
        src1rv2 = GetNamedSwizzle(src1, m)

        print("\t{} = {} < {} ? {} : {}; // LT {} {} {}".format(
            fTempList[i],
            GetNamedSwizzle(src0, m),
            GetNamedSwizzle(src1, m),
            HardCastToF32(iTrue),
            HardCastToF32(iFalse),
            dst, src0, src1
        ))

        #print("uint32_t {} = {};".format(rv1, HardCastToI32(src0rv1)))
        #print("uint32_t {} = {};".format(rv2, src1rv2))
        #print("{} = {} + {};".format(dst, HardCastToI32(rv1), HardCastToI32(rv2)))
        
    for i in range(sl):
    #    s, m = GetMaskAndIndex(dst, i)
        
        print("\t{} = {};".format(
            GetNamedSwizzle(dst, i),
            fTempList[i]
        ))
    print("}")

    # for i in range(sl):
    #     s, m = GetMaskAndIndex(dst, i)
    #     print("{} = {} < {} ? {} : {}; // LT {} {} {}".format(
    #         GetNamedSwizzle(dst, i),
    #         GetNamedSwizzle(src0, m),
    #         GetNamedSwizzle(src1, m),
    #         HardCastToF32(iTrue),
    #         HardCastToF32(iFalse),
    #         dst, src0, src1
    #     ))

def ILT(xs):
    # dst, sl = Dstify(xs[0])
    # src0 = Sane(xs[1], sl)
    # src1 = Sane(xs[2], sl)

    # print("{} = {} < {};".format(dst, src0, src1))

    dst, sl = Dstify(xs[0])
    src0 = xs[1]
    src1 = xs[2]

    # indices = GetSwizzleIndices(dst, sl)
    # src0 = CreateVectorFromSrc(src0, indices)
    # src1 = CreateVectorFromSrc(src1, indices)

    #print("{} = {} < {};".format(dst, src0, src1))
    print("{")
    for i in range(sl):
        s, m = GetMaskAndIndex(dst, i)
        #rv1 = CreateTemp()
        #rv2 = CreateTemp()

        src0rv1 = GetNamedSwizzle(src0, m)
        src1rv2 = GetNamedSwizzle(src1, m)

        print("\t{} = {} < {} ? {} : {}; // ILT {} {} {}".format(
            iTempList[i],
            HardCastToI32(GetNamedSwizzle(src0, m)),
            HardCastToI32(GetNamedSwizzle(src1, m)),
            HardCastToI32(iTrue),
            HardCastToI32(iFalse),
            dst, src0, src1
        ))

        #print("uint32_t {} = {};".format(rv1, HardCastToI32(src0rv1)))
        #print("uint32_t {} = {};".format(rv2, src1rv2))
        #print("{} = {} + {};".format(dst, HardCastToI32(rv1), HardCastToI32(rv2)))
        
    for i in range(sl):
    #    s, m = GetMaskAndIndex(dst, i)
        print("\t{} = {};".format(
            GetNamedSwizzle(dst, i),
            HardCastToF32(iTempList[i])
        ))

    print("}")
    # for i in range(sl):
    #     s, m = GetMaskAndIndex(dst, i)
    #     print("{} = {} < {} ? {} : {}; // ILT".format(
    #         GetNamedSwizzle(dst, i),
    #         HardCastToI32(GetNamedSwizzle(src0, m)),
    #         HardCastToI32(GetNamedSwizzle(src1, m)),
    #         HardCastToF32(iTrue),
    #         HardCastToF32(iFalse)
    #     ))

def ULT(xs):
    # dst, sl = Dstify(xs[0])
    # src0 = Sane(xs[1], sl)
    # src1 = Sane(xs[2], sl)

    # print("{} = {} < {};".format(dst, src0, src1))

    dst, sl = Dstify(xs[0])
    src0 = xs[1]
    src1 = xs[2]

    # indices = GetSwizzleIndices(dst, sl)
    # src0 = CreateVectorFromSrc(src0, indices)
    # src1 = CreateVectorFromSrc(src1, indices)

    #print("{} = {} < {};".format(dst, src0, src1))

    print("{")
    for i in range(sl):
        s, m = GetMaskAndIndex(dst, i)
        #rv1 = CreateTemp()
        #rv2 = CreateTemp()

        src0rv1 = GetNamedSwizzle(src0, m)
        src1rv2 = GetNamedSwizzle(src1, m)

        print("\t{} = {} < {} ? {} : {}; // ULT {} {} {}".format(
            uTempList[i],
            HardCastToU32(GetNamedSwizzle(src0, m)),
            HardCastToU32(GetNamedSwizzle(src1, m)),
            HardCastToU32(iTrue),
            HardCastToU32(iFalse),
            dst, src0, src1
        ))

        #print("uint32_t {} = {};".format(rv1, HardCastToI32(src0rv1)))
        #print("uint32_t {} = {};".format(rv2, src1rv2))
        #print("{} = {} + {};".format(dst, HardCastToI32(rv1), HardCastToI32(rv2)))
        
    for i in range(sl):
    #    s, m = GetMaskAndIndex(dst, i)
        print("\t{} = {};".format(
            GetNamedSwizzle(dst, i),
            HardCastToF32(uTempList[i])
        ))

    print("}")

def GE(xs):
    dst, sl = Dstify(xs[0])
    src0 = xs[1]
    src1 = xs[2]

    # indices = GetSwizzleIndices(dst, sl)
    # src0 = CreateVectorFromSrc(src0, indices)
    # src1 = CreateVectorFromSrc(src1, indices)

    print("{")
    for i in range(sl):
        s, m = GetMaskAndIndex(dst, i)
        #rv1 = CreateTemp()
        #rv2 = CreateTemp()

        src0rv1 = GetNamedSwizzle(src0, m)
        src1rv2 = GetNamedSwizzle(src1, m)

        print("\t{} = {} > {} ? {} : {}; // FGE {} {} {}".format(
            fTempList[i],
            GetNamedSwizzle(src0, m),
            GetNamedSwizzle(src1, m),
            HardCastToF32(iTrue),
            HardCastToF32(iFalse),
            dst, src0, src1
        ))

        #print("uint32_t {} = {};".format(rv1, HardCastToI32(src0rv1)))
        #print("uint32_t {} = {};".format(rv2, src1rv2))
        #print("{} = {} + {};".format(dst, HardCastToI32(rv1), HardCastToI32(rv2)))
        
    for i in range(sl):
    #    s, m = GetMaskAndIndex(dst, i)
        print("\t{} = {};".format(
            GetNamedSwizzle(dst, i),
            fTempList[i]
        ))

    print("}")

def IGE(xs):
    dst, sl = Dstify(xs[0])
    src0 = xs[1]
    src1 = xs[2]

    # indices = GetSwizzleIndices(dst, sl)
    # src0 = CreateVectorFromSrc(src0, indices)
    # src1 = CreateVectorFromSrc(src1, indices)

    print("{")
    for i in range(sl):
        s, m = GetMaskAndIndex(dst, i)
        #rv1 = CreateTemp()
        #rv2 = CreateTemp()

        src0rv1 = GetNamedSwizzle(src0, m)
        src1rv2 = GetNamedSwizzle(src1, m)

        print("\t{} = {} > {} ? {} : {}; // IGE {} {} {}".format(
            iTempList[i],
            HardCastToI32(GetNamedSwizzle(src0, m)),
            HardCastToI32(GetNamedSwizzle(src1, m)),
            HardCastToI32(iTrue),
            HardCastToI32(iFalse),
            dst, src0, src1
        ))

        #print("uint32_t {} = {};".format(rv1, HardCastToI32(src0rv1)))
        #print("uint32_t {} = {};".format(rv2, src1rv2))
        #print("{} = {} + {};".format(dst, HardCastToI32(rv1), HardCastToI32(rv2)))
        
    for i in range(sl):
    #    s, m = GetMaskAndIndex(dst, i)
        print("\t{} = {};".format(
            GetNamedSwizzle(dst, i),
            HardCastToF32(iTempList[i])
        ))

    print("}")

    # for i in range(sl):
    #     s, m = GetMaskAndIndex(dst, i)
    #     print("{} = {} < {} ? {} : {}; // LT {} {} {}".format(
    #         GetNamedSwizzle(dst, i),
    #         HardCastToI32(GetNamedSwizzle(src0, m)),
    #         HardCastToI32(GetNamedSwizzle(src1, m)),
    #         HardCastToF32(iTrue),
    #         HardCastToF32(iFalse),
    #         dst, src0, src1
    #     ))


def INE(xs):
    dst, sl = Dstify(xs[0])
    src0 = xs[1]
    src1 = xs[2]

    # indices = GetSwizzleIndices(dst, sl)
    # src0 = CreateVectorFromSrc(src0, indices)
    # src1 = CreateVectorFromSrc(src1, indices)

    print("{")
    for i in range(sl):
        s, m = GetMaskAndIndex(dst, i)
        #rv1 = CreateTemp()
        #rv2 = CreateTemp()

        src0rv1 = GetNamedSwizzle(src0, m)
        src1rv2 = GetNamedSwizzle(src1, m)

        print("\t{} = {} != {} ? {} : {}; // INE {} {} {}".format(
            iTempList[i],
            HardCastToI32(GetNamedSwizzle(src0, m)),
            HardCastToI32(GetNamedSwizzle(src1, m)),
            HardCastToI32(iTrue),
            HardCastToI32(iFalse),
            dst, src0, src1
        ))

        #print("uint32_t {} = {};".format(rv1, HardCastToI32(src0rv1)))
        #print("uint32_t {} = {};".format(rv2, src1rv2))
        #print("{} = {} + {};".format(dst, HardCastToI32(rv1), HardCastToI32(rv2)))
        
    for i in range(sl):
    #    s, m = GetMaskAndIndex(dst, i)
        print("\t{} = {};".format(
            GetNamedSwizzle(dst, i),
            HardCastToF32(iTempList[i])
        ))

    print("}")

    # for i in range(sl):
    #     s, m = GetMaskAndIndex(dst, i)
    #     print("{} = {} != {} ? {} : {};".format(
    #         GetNamedSwizzle(dst, i),
    #         GetNamedSwizzle(src0, m),
    #         GetNamedSwizzle(src1, m),
    #         HardCastToF32(iTrue),
    #         HardCastToF32(iFalse)
    #     ))

def EQ(xs):
    # dst, sl = Dstify(xs[0])
    # src0 = Sane(xs[1], sl)
    # src1 = Sane(xs[2], sl)

    # print("{} = {} == {};".format(dst, src0, src1))

    dst, sl = Dstify(xs[0])
    src0 = xs[1]
    src1 = xs[2]

    # indices = GetSwizzleIndices(dst, sl)
    # src0 = CreateVectorFromSrc(src0, indices)
    # src1 = CreateVectorFromSrc(src1, indices)

    #print("{} = {} == {};".format(dst, src0, src1))

    print("{")
    for i in range(sl):
        s, m = GetMaskAndIndex(dst, i)
        #rv1 = CreateTemp()
        #rv2 = CreateTemp()

        src0rv1 = GetNamedSwizzle(src0, m)
        src1rv2 = GetNamedSwizzle(src1, m)

        print("\t{} = {} == {} ? {} : {}; // EQ {} {} {}".format(
            iTempList[i],
            GetNamedSwizzle(src0, m),
            GetNamedSwizzle(src1, m),
            HardCastToI32(iTrue),
            HardCastToI32(iFalse),
            dst, src0, src1
        ))

        #print("uint32_t {} = {};".format(rv1, HardCastToI32(src0rv1)))
        #print("uint32_t {} = {};".format(rv2, src1rv2))
        #print("{} = {} + {};".format(dst, HardCastToI32(rv1), HardCastToI32(rv2)))
        
    for i in range(sl):
    #    s, m = GetMaskAndIndex(dst, i)
        print("\t{} = {};".format(
            GetNamedSwizzle(dst, i),
            HardCastToF32(iTempList[i])
        ))

    print("}")

    # for i in range(sl):
    #     s, m = GetMaskAndIndex(dst, i)
    #     print("{} = {} == {} ? {} : {};".format(
    #         GetNamedSwizzle(dst, i),
    #         GetNamedSwizzle(src0, m),
    #         GetNamedSwizzle(src1, m),
    #         HardCastToF32(iTrue),
    #         HardCastToF32(iFalse)
    #     ))

def IEQ(xs):
    # dst, sl = Dstify(xs[0])
    # src0 = Sane(xs[1], sl)
    # src1 = Sane(xs[2], sl)

    # print("{} = {} == {};".format(dst, src0, src1))

    dst, sl = Dstify(xs[0])
    src0 = xs[1]
    src1 = xs[2]

    # indices = GetSwizzleIndices(dst, sl)
    # src0 = CreateVectorFromSrc(src0, indices)
    # src1 = CreateVectorFromSrc(src1, indices)

    #print("{} = {} == {};".format(dst, src0, src1))


    print("{")
    for i in range(sl):
        s, m = GetMaskAndIndex(dst, i)
        #rv1 = CreateTemp()
        #rv2 = CreateTemp()

        src0rv1 = GetNamedSwizzle(src0, m)
        src1rv2 = GetNamedSwizzle(src1, m)

        print("\t{} = {} == {} ? {} : {}; // IEQ {} {} {}".format(
            iTempList[i],
            HardCastToI32(GetNamedSwizzle(src0, m)),
            HardCastToI32(GetNamedSwizzle(src1, m)),
            HardCastToI32(iTrue),
            HardCastToI32(iFalse),
            dst, src0, src1
        ))

        #print("uint32_t {} = {};".format(rv1, HardCastToI32(src0rv1)))
        #print("uint32_t {} = {};".format(rv2, src1rv2))
        #print("{} = {} + {};".format(dst, HardCastToI32(rv1), HardCastToI32(rv2)))
        
    for i in range(sl):
    #    s, m = GetMaskAndIndex(dst, i)
        print("\t{} = {};".format(
            GetNamedSwizzle(dst, i),
            HardCastToF32(iTempList[i])
        ))

    print("}")


    # for i in range(sl):
    #     s, m = GetMaskAndIndex(dst, i)
    #     print("{} = {} == {} ? {} : {}; // IEQ {} {} {}".format(
    #         GetNamedSwizzle(dst, i),
    #         HardCastToI32(GetNamedSwizzle(src0, m)),
    #         HardCastToI32(GetNamedSwizzle(src1, m)),
    #         HardCastToF32(iTrue),
    #         HardCastToF32(iFalse),
    #         dst, src0, src1
    #     ))

def AND(xs):
    # dst, sl = Dstify(xs[0])
    # src0 = Sane(xs[1], sl)
    # src1 = Sane(xs[2], sl)

    # print("{} = {} && {};".format(dst, src0, src1))

    dst, sl = Dstify(xs[0])
    src0 = xs[1]
    src1 = xs[2]

    # indices = GetSwizzleIndices(dst, sl)
    # src0 = CreateVectorFromSrc(src0, indices)
    # src1 = CreateVectorFromSrc(src1, indices)

    #print("{} = {} && {};".format(dst, src0, src1))

    # Create a temp every time...

    print("{")
    for i in range(sl):
        s, m = GetMaskAndIndex(dst, i)
        #rv1 = CreateTemp()
        #rv2 = CreateTemp()

        src0rv1 = GetNamedSwizzle(src0, m)
        src1rv2 = GetNamedSwizzle(src1, m)

        print("\t{} = {} & {}; // AND {} {} {}".format(
            iTempList[i],
            HardCastToI32(GetNamedSwizzle(src0, m)),
            HardCastToI32(GetNamedSwizzle(src1, m)),
            dst, src0, src1
        ))

        #print("uint32_t {} = {};".format(rv1, HardCastToI32(src0rv1)))
        #print("uint32_t {} = {};".format(rv2, src1rv2))
        #print("{} = {} + {};".format(dst, HardCastToI32(rv1), HardCastToI32(rv2)))
        
    for i in range(sl):
    #    s, m = GetMaskAndIndex(dst, i)
        print("\t{} = {};".format(
            GetNamedSwizzle(dst, i),
            HardCastToF32(iTempList[i])
        ))

    print("}")

    # for i in range(sl):
    #     s, m = GetMaskAndIndex(dst, i)

    #     #temp = CreateTemp()
    #     #print("{} = ")
    #     #HardCast

    #     #iTe = CreateTemp()
    #     print("{} = {} & {};".format(iRV0,
    #             HardCastToI32(GetNamedSwizzle(src0, m)),
    #             HardCastToI32(GetNamedSwizzle(src1, m))
    #             ))

    #     print("{} = {};".format(
    #         GetNamedSwizzle(dst, i),
    #         HardCastToF32(iRV0)
    #         )
    #     )

def OR(xs):
    # dst, sl = Dstify(xs[0])
    # src0 = Sane(xs[1], sl)
    # src1 = Sane(xs[2], sl)

    # print("{} = {} || {};".format(dst, src0, src1))

    dst, sl = Dstify(xs[0])
    src0 = xs[1]
    src1 = xs[2]

    #indices = GetSwizzleIndices(dst, sl)
    #src0 = CreateVectorFromSrc(src0, indices)
    #src1 = CreateVectorFromSrc(src1, indices)

    #print("{} = {} || {};".format(dst, src0, src1))

    print("{")
    for i in range(sl):
        s, m = GetMaskAndIndex(dst, i)
        #rv1 = CreateTemp()
        #rv2 = CreateTemp()

        src0rv1 = GetNamedSwizzle(src0, m)
        src1rv2 = GetNamedSwizzle(src1, m)

        print("\t{} = {} | {}; // OR {} {} {}".format(
            iTempList[i],
            HardCastToI32(GetNamedSwizzle(src0, m)),
            HardCastToI32(GetNamedSwizzle(src1, m)),
            dst, src0, src1
        ))

        #print("uint32_t {} = {};".format(rv1, HardCastToI32(src0rv1)))
        #print("uint32_t {} = {};".format(rv2, src1rv2))
        #print("{} = {} + {};".format(dst, HardCastToI32(rv1), HardCastToI32(rv2)))
        
    for i in range(sl):
    #    s, m = GetMaskAndIndex(dst, i)
        print("\t{} = {};".format(
            GetNamedSwizzle(dst, i),
            HardCastToF32(iTempList[i])
        ))

    print("}")

    # for i in range(sl):
    #     s, m = GetMaskAndIndex(dst, i)

    #     #temp = CreateTemp()
    #     #print("{} = ")
    #     #HardCast

    #     #iTe = CreateTemp()
    #     print("{} = {} | {};".format(iRV0,
    #             HardCastToI32(GetNamedSwizzle(src0, m)),
    #             HardCastToI32(GetNamedSwizzle(src1, m))
    #             ))

    #     print("{} = {};".format(
    #         GetNamedSwizzle(dst, i),
    #         HardCastToF32(iRV0)
    #         )
    #     )

def SHL(xs):
    dst, sl = Dstify(xs[0])
    src0 = xs[1]
    src1 = xs[2]

    for i in range(sl):
        s, m = GetMaskAndIndex(dst, i)

        print("{} = {} << {};".format(iRV0,
                HardCastToI32(GetNamedSwizzle(src0, m)),
                src1[9:-1]                ))

        print("{} = {};".format(
            GetNamedSwizzle(dst, i),
            HardCastToF32(iRV0)
            )
        )

    # for i in range(sl):
    #     s, m = GetMaskAndIndex(dst, i)
    #     print("{} = float(int32_t({}) << {});".format(
    #         GetNamedSwizzle(dst, i),
    #         GetNamedSwizzle(src0, m),
    #         GetNamedSwizzle(src1, m)
    #     ))
    
def UTOF(xs):
    dst, sl = Dstify(xs[0])
    src0 = xs[1]

    for i in range(sl):
        s, m = GetMaskAndIndex(dst, i)

        print("{} = {};".format(iRV0,
                HardCastToI32(GetNamedSwizzle(src0, m))
                ))

        print("{} = float({}); // UTOF softcast".format(
            GetNamedSwizzle(dst, i),
            iRV0
            )
        )

# HardCastToI32(

#         print("{} = {}; // Pretend we weren't already a float :P".format(
#             GetNamedSwizzle(dst, i),
#             GetNamedSwizzle(src0, m)
#         ))

def FTOU(xs):
    dst, sl = Dstify(xs[0])
    src0 = xs[1]

    for i in range(sl):
        s, m = GetMaskAndIndex(dst, i)

        print("{} = uint32_t({}); //FTOU softcast".format(iRV0,
                    GetNamedSwizzle(src0, m)
                ))

        print("{} = {}; // FTOU hardcast".format(
            GetNamedSwizzle(dst, i),
            HardCastToF32(iRV0)
            )
        )

def MAX(xs):
    dst, sl = Dstify(xs[0])
    src0 = xs[1]
    src1 = xs[2]

    for i in range(sl):
        s, m = GetMaskAndIndex(dst, i)
        print("{} = max({}, {});".format(
            GetNamedSwizzle(dst, i),
            GetNamedSwizzle(src0, m),
            GetNamedSwizzle(src1, m)
        ))

def MIN(xs):
    dst, sl = Dstify(xs[0])
    src0 = xs[1]
    src1 = xs[2]

    for i in range(sl):
        s, m = GetMaskAndIndex(dst, i)
        print("{} = min({}, {});".format(
            GetNamedSwizzle(dst, i),
            GetNamedSwizzle(src0, m),
            GetNamedSwizzle(src1, m)
        ))

def IMAX(xs):
    dst, sl = Dstify(xs[0])
    src0 = xs[1]
    src1 = xs[2]

    print("{")
    for i in range(sl):
        s, m = GetMaskAndIndex(dst, i)
        #rv1 = CreateTemp()
        #rv2 = CreateTemp()

        src0rv1 = GetNamedSwizzle(src0, m)
        src1rv2 = GetNamedSwizzle(src1, m)

        print("\t{} = max({}, {}); // IMAX {} {} {}".format(
            iTempList[i],
            HardCastToI32(GetNamedSwizzle(src0, m)),
            HardCastToI32(GetNamedSwizzle(src1, m)),
            dst, src0, src1
        ))

        #print("uint32_t {} = {};".format(rv1, HardCastToI32(src0rv1)))
        #print("uint32_t {} = {};".format(rv2, src1rv2))
        #print("{} = {} + {};".format(dst, HardCastToI32(rv1), HardCastToI32(rv2)))
        
    for i in range(sl):
    #    s, m = GetMaskAndIndex(dst, i)
        print("\t{} = {};".format(
            GetNamedSwizzle(dst, i),
            HardCastToF32(iTempList[i])
        ))

    print("}")

    # for i in range(sl):
    #     s, m = GetMaskAndIndex(dst, i)
    #     print("{} = max({}, {});".format(
    #         GetNamedSwizzle(dst, i),
    #         GetNamedSwizzle(src0, m),
    #         GetNamedSwizzle(src1, m)
    #     ))

def IMIN(xs):
    dst, sl = Dstify(xs[0])
    src0 = xs[1]
    src1 = xs[2]

    for i in range(sl):
        s, m = GetMaskAndIndex(dst, i)
        print("{} = min({}, {}); //IMINN".format(
            GetNamedSwizzle(dst, i),
            GetNamedSwizzle(src0, m),
            GetNamedSwizzle(src1, m)
        ))

def FTOI(xs):
    dst, sl = Dstify(xs[0])
    src0 = xs[1]

    for i in range(sl):
        s, m = GetMaskAndIndex(dst, i)

        print("{} = int32_t({}); //FTOI softcast".format(iRV0,
                    GetNamedSwizzle(src0, m)
                ))

        print("{} = {}; // FTOI hardcast".format(
            GetNamedSwizzle(dst, i),
            HardCastToF32(iRV0)
            )
        )

def DOT(xs, v):
    dst, sl = Dstify(xs[0])
    src0 = xs[1]
    src1 =''.join(xs[2:])

    src0 = '.'.join(src0.split(".")[:-1]) + "." + ''.join(src0.split(".")[-1][:v])
    src1 = '.'.join(src1.split(".")[:-1]) + "." + ''.join(src1.split(".")[-1][:v])

    # Remove Negatives
    if src0.startswith("-"):
        src0 = "-" + CppVec(v, src0[1:])
    else:
        src0 = CppVec(v, src0)

    if src1.startswith("-"):
        src1 = "-" + CppVec(v, src1[1:])
    else:
        src1 = CppVec(v, src1)

    print("{} = dot({}, {});".format(dst, src0, src1))

def BREAKZERO(xs):
    dst, sl = Dstify(xs[0])
    print("if ({} == 0) {{ break; }}".format(HardCastToI32(dst))) 

def IFNZ(xs):
    dst, sl = Dstify(xs[0])
    print("if ({} != 0) {{".format(HardCastToI32(dst)) )

def IFZ(xs):
    dst, sl = Dstify(xs[0])
    print("if ({} == 0) {{".format(HardCastToI32(dst)))

def INEG(xs):
    dst, sl = Dstify(xs[0])
    src0 = xs[1]

    # Throw it to int
    print("{} = -1 * {};".format(iRV0,
            HardCastToI32(src0)
            ))

    print("{} = {};".format(dst, HardCastToF32(iRV0))) 

def LD(xs):
    dst, sl = Dstify(xs[0])
    src0 = xs[1]
    src1 = xs[2]
    # print("{} = {}[uint32_t({})].{};".format(
    #         dst, src1.split(".")[0], src0, src1.split(".")[1][:sl]
    #     )) 

    vStart = src0.split(".")[0]
    vEnd = src0.split(".")[1]

    print("{} = {};".format(
        iRV0,
        HardCastToI32(vStart + "." + vEnd[0])
    ))

    for i in range(sl):
        s, m = GetMaskAndIndex(dst, i)
        print("{} = {}[{}].{};".format(
            GetNamedSwizzle(dst, i),
            GetNamedSwizzle(src1, m).split(".")[0],
            iRV0,
            GetNamedSwizzle(src1, m).split(".")[1],
        ))

def RSQ(xs):
    dst, sl = Dstify(xs[0])
    src0 = xs[1]
    # print("{} = {}[uint32_t({})].{};".format(
    #         dst, src1.split(".")[0], src0, src1.split(".")[1][:sl]
    #     )) 

    for i in range(sl):
        s, m = GetMaskAndIndex(dst, i)
        print("{} = 1.f / sqrt({});".format(
            GetNamedSwizzle(dst, i),
            GetNamedSwizzle(src0, m)
        ))

def SQRT(xs):
    dst, sl = Dstify(xs[0])
    src0 = xs[1]
    # print("{} = {}[uint32_t({})].{};".format(
    #         dst, src1.split(".")[0], src0, src1.split(".")[1][:sl]
    #     )) 

    for i in range(sl):
        s, m = GetMaskAndIndex(dst, i)
        print("{} = sqrt({});".format(
            GetNamedSwizzle(dst, i),
            GetNamedSwizzle(src0, m)
        ))

def MOVC(xs):
    dst, sl = Dstify(xs[0])
    comp = xs[1]
    src0 = xs[2]
    src1 = xs[3]

    print("{")
    for i in range(sl):
        s, m = GetMaskAndIndex(dst, i)
        #rv1 = CreateTemp()
        #rv2 = CreateTemp()

        src0rv1 = GetNamedSwizzle(src0, m)
        src1rv2 = GetNamedSwizzle(src1, m)

        print("\t{} = {} ? {} : {}; // MOVC {} {} {}".format(
            fTempList[i],
            HardCastToI32(GetNamedSwizzle(comp, m)),
            HardCastToF32(GetNamedSwizzle(src0, m)),
            HardCastToF32(GetNamedSwizzle(src1, m)),
            dst, src0, src1
        ))

        #print("uint32_t {} = {};".format(rv1, HardCastToI32(src0rv1)))
        #print("uint32_t {} = {};".format(rv2, src1rv2))
        #print("{} = {} + {};".format(dst, HardCastToI32(rv1), HardCastToI32(rv2)))
        
    for i in range(sl):
    #    s, m = GetMaskAndIndex(dst, i)
        print("\t{} = {};".format(
            GetNamedSwizzle(dst, i),
            fTempList[i]
        ))

    print("}")

    # for i in range(sl):
    #     s, m = GetMaskAndIndex(dst, i)
    #     print("{} = {} ? {} : {};".format(
    #         GetNamedSwizzle(dst, i),
    #         HardCastToI32(GetNamedSwizzle(comp, m)),
    #         GetNamedSwizzle(src0, m),
    #         GetNamedSwizzle(src1, m)
    #     ))

    #print("{} = {} ? {} : {};".format(dst, comp, src0, src1))




data = []

with open(sys.argv[1], "r") as f:
    data = f.read()

data = data.split("\n")



print("uint32_t {} = 0xFFFFFFFF;".format(iTrue))
print("uint32_t {} = 0x0;".format(iFalse))
print("uint32_t {} = 0x0;".format(iRV0))

for i in iTempList:
    print("int32_t {} = 0x0;".format(i))

for i in uTempList:
    print("uint32_t {} = 0x0;".format(i))

for i in fTempList:
    print("float {} = 0x0;".format(i))

for line in data:
    a = line
    a = a.replace("(","\"(")
    a = a.replace("l\"(","\"_CONVERT(")
    a = a.replace(")",")\"")


    a = shlexsplit(a)
    if len(a) > 2 and a[1].startswith("[precise"): 
        a = a[:1] + a[2:]

    command = a[0]

    if command == "mul":
        MUL(a[1:])
    elif command == "add":
        ADD(a[1:])
    elif command == "sincos":
        SINCOS(a[1:])
    elif command == "mov":
        MOV(a[1:])
    elif command == "lt":
        LT(a[1:])
    elif command == "movc":
        MOVC(a[1:])
    elif command == "ftoi":
        FTOI(a[1:])
    elif command == "ilt":
        ILT(a[1:])
    elif command == "ult":
        ULT(a[1:])
    elif command == "ige":
        IGE(a[1:])
    elif command == "and":
        AND(a[1:])
    elif command == "ine":
        INE(a[1:])
    elif command == "eq":
        EQ(a[1:])
    elif command == "ieq":
        IEQ(a[1:])
    elif command == "loop":
        print("while(true) {")
    elif command == "endloop":
        print("}")
    elif command == "dp4":
        DOT(a[1:], 4)
    elif command == "dp3":
        DOT(a[1:], 3)
    elif command == "dp2":
        DOT(a[1:], 2)
    elif command == "breakc_z":
        BREAKZERO(a[1:])
    elif command == "ineg":
        INEG(a[1:])
    elif command == "iadd":
        ADD(a[1:], True)
    elif command == "or":
        OR(a[1:])
    elif command == "ishl":
        SHL(a[1:])
    elif command == "utof":
        UTOF(a[1:])
    elif command == "ftou":
        FTOU(a[1:])
    elif command.startswith("ld_indexable"):
        LD(a[1:])
    elif command == "if_nz":
        IFNZ(a[1:])
    elif command == "imax":
        IMAX(a[1:])
    elif command == "max":
        MAX(a[1:])
    elif command == "endif":
        print("}")
    elif command == "div":
        DIV(a[1:])
    elif command == "rsq":
        RSQ(a[1:])
    elif command == "sqrt":
        SQRT(a[1:])
    elif command == "else":
        print("} else {")
    elif command == "ge":
        GE(a[1:])
    elif command == "mad":
        FMA(a[1:])
    elif command == "if_z":
        IFZ(a[1:])
    elif command == "min":
        MIN(a[1:])
    elif command == "div_sat":
        DIVSAT(a[1:])
    elif command == "add_sat":
        ADDSAT(a[1:])
    elif command == "log":
        LOG(a[1:])
    elif command == "exp":
        EXP(a[1:])
    elif command == "round_pi":
        CEIL(a[1:])
    elif command == "round_pi_sat":
        CEILSAT(a[1:])
    elif command == "round_z":
        ROUND_TO_ZERO(a[1:])
    else:
        raise Exception(command)