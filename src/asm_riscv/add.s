    .section .text
    .global add
    
add:
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
    and x30, a1, x5
    #存储x，y的符号位
    j compare_sign

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
    and x30, a1, x5
    #存储x，y的符号位

compare_sign:
    #符号相同直接计算
    beq x29, x30, add1
    #符号不相同判断正负
    beq x30, x0, compare2
    #x的符号为1，即x为负，y为正

compare1:  #比较绝对值大小，此时x为正，y为负
    bge x6, x28, sub1
    #x尾数大于y尾数，跳转sub1计算
    j sub2

compare2:  #比较绝对值大小，此时x为负，y为正
    bge x6, x28, sub3
    #x尾数大于y尾数，跳转sub3计算
    j sub4

sub1:  #x的符号为0，即x为正，y为负(x>=y)
    sub x6, x6, x28
    j add_mant
    #x6储存绝对值，x29储存符号，为正

sub2:  #x的符号为0，即x为正，y为负(x<y)
    sub x6, x28, x6
    add x29, x30, x0
    j add_mant
    #x6储存绝对值，x29储存符号，为负

sub3:  #x的符号为1，即x为负，y为正(x>=y)
    sub x6, x6, x28
    j add_mant
    #x6储存绝对值，x29储存符号，为负

sub4:  #x的符号为1，即x为负，y为正(x<y)
    sub x6, x28, x6
    add x29, x30, x0
    j add_mant
    #x6储存绝对值，x29储存符号，为正

add1:  #x与y符号相同
    add x6, x6, x28
    and x29, x29, x30
    #x6储存绝对值，x29储存符号

add_mant:
    li x30, 0x00800000
    blt x6, x30, normalize_loop  #尾数<隐含位需要规格化左移
    #右移，尾数>=隐含位
    li x30, 0x01000000
    blt x6, x30, normalize1 #尾数小于25位
    #尾数25位
    srai x6, x6, 1
    addi x31, x31, 1  # Increment the exp
    li x30, 0x00800000
    sub x6, x6, x30
    j no_shift

normalize1:
    li x30, 0x00800000
    #尾数大于隐含位小于25位
    sub x6, x6, x30
    j no_shift

normalize_loop:
    slli x6, x6, 1 #尾数左移
    addi x31, x31, -1 #指数-1
    blt x6, x30, normalize_loop #判断是否>=隐含位
    sub x6, x6, x30
    #由于此时是在小于隐藏位时左移，所以最终需要左移一位，使得x6的1在隐藏位上，并消除1，得到最终结果
    #最终得到x6为规格化后的值，x29储存符号位

no_shift:    
    # overflow
    li x30, 0x000000FF
    bgeu x31, x30, overflow  # if exp >= 0xFF overflow
    slli x31, x31, 23
    or x6, x6, x31
    or a0, x6, x29
    j end

overflow:
    li a0, 0x7F800000

end:
    ret
