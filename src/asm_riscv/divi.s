    .section .text
    .global divi

divi: 
    li x29, 0x7F800000
    and x5, a0, x29 #获得x的指数
    and x7, a1, x29 #获得y的指数
    li x29, 0x007FFFFF
    and x6 , a0, x29 #获得x的尾数
    and x28, a1, x29 #获得y的尾数
    # x5, x6 <= a0 ; x7, x28 <= a1

    srli x29, x5, 23 #保存x的指数到低8位
    srli x30, x7, 23 #保存y的指数到低8位

    bge x29, x30, adjust_y  # if exp(x) >= exp(y), adjust y; else adjust x

adjust_x:
    sub x31, x30, x29
    #增加隐藏位
    li x5, 0x00800000
    or x6, x6, x5
    or x28, x28, x5
    #y大，x移位
    sra x6, x6, x31
    add x31, x30, x0
    #此时x30，x29可以自由存储
    li x5, 0x80000000
    and x29, a0, x5
    #x的符号为1，即x为负，y为正(x<y)
    sub x28, x28, x6
    add x29, x30, x0
    j add

adjust_y:
    sub x31, x29, x30
    #增加隐藏位
    li x5, 0x00800000
    or x6, x6, x5
    or x28, x28, x5
    #x大，y移位
    sra x28, x28, x31
    add x31, x29, x0
    #此时x30，x29可以自由存储
    li x5, 0x80000000
    and x29, a0, x5
    #x的符号为1，即x为负，y为正(x<y)
    sub x6, x6, x28
    add x29, x30, x0
    j add

add:
    #x的符号为1，即x为负，y为正(x<y)
    sub x6, x6, x28
    add x29, x30, x0
    j add_mant

add_mant:
    #x的符号为1，即x为负，y为正(x<y)
    sub x6, x6, x28
    add x29, x30, x0
    j add


