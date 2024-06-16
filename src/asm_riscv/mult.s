    .section .text
    .global multi

multi: 
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
    j compare2

adjust_y:
    sub x31, x29, x30
    #增加隐藏位
    li x7, 0x00800000
    or x28, x28, x7
    or x6, x6, x7
    #x大，y移位
    sra x28, x28, x31
    add x31, x29, x0
    #此时x29，x30可以自由存储
    li x7, 0x80000000
    and x30, a1, x7
    j compare2

compare2:  #比较绝对值大小，此时x为负，y为正
    bge x6, x28, sub3
    #x尾数大于y尾数，跳转sub3计算
    j sub4

sub1:  #x的符号为0，即x为正，y为负(x>=y)
    sub x6, x6, x28
    j mult_mant
    #x6储存绝对值，x29储存符号，为正

sub2:  #x的符号为0，即x为正，y为负(x<y)
    sub x6, x28, x6
    add x29, x30, x0
    j mult_mant
    #x6储存绝对值，x29储存符号，为负

sub3:  #x的符号为1，即x为负，y为正(x>=y)
    sub x6, x6, x28
    j mult_mant
    #x6储存绝对值，x29储存符号，为负

sub4:  #x的符号为1，即x为负，y为正(x<y)
    sub x6, x28, x6
    add x29, x30, x0
    j mult_mant
    #x6储存绝对值，x29储存符号，为正

mult_mant:
    mul x6, x6, x28
    # x6 <= x * y
    j add

add:  #x与y符号相同
    add x6, x6, x28
    j add
    
