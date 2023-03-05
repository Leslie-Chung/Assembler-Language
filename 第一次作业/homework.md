# 1.简要说明寄存器EAX与寄存器AX，AH和AL的关系，并写出如下程序片段中每条指令执行后寄存器EAX的内容（具体请参见教材P55 题6）

- *我的答案：**16.6*分

  AX 是 EAX 的低16位，AH 是 AX 的高8位，AL 是 AX 的低八位

  ​                      EAX的值

  89ABC H

  81234 H

  81298 H

  87698 H

  87619 H

  876e4 H

  8765a H

  8d15a H

  8d22c H

  8d12d H

  91694 H

  8a040 H 

- *正确答案：*

MOV  EAX,89ABCH

EAX=89ABCH



MOV AX,1234H

AX=1234H

EAX=81234H



MOV AL,98H

AL=98H

AX=1298H

EAX=81298H



MOV AH,76H

AH=76H

AX=7698H

EAX=87698H



ADD AL,81H

AL=81+98=19H（进位到CF，但因为指令是ADD，并没有携带进高位AH）

AX=7619H

EAX=87619H



SUB AL, 35H 

AL=19-35=19+CB=E4H（不够从CF借位，但因为指令为SUB而非SBB，所以不记录借位）

EAX = 876E4H



ADD AL, AH  

AL=E4+76=5AH

EAX = 8765AH（同理，进位只记录在CF里而没有携带进来，也就是此时CF=1）



ADC AH, AL

AH=76+5A+CF=D1H

 EAX = 8D15AH



ADD AX, 0D2H

AX=D15A+0D2=D22CH 

EAX = 8D22CH



SUB AX，0FFH 

AX=D22C-0FF=D22C+FF01=D12DH

EAX = 8D12DH

ADD EAX, 4567H

EAX=8D12D+4567=91694 H

EAX = 91694H



SUB EAX, 7654H 

EAX=91694-7654=91694+FFFF89AC=8A040H

EAX = 8A040H



借助DOSBOX+debug32得到的截图如下：

![1-1.png](https://p.ananas.chaoxing.com/star3/origin/126e92eae2ccfef213da10028977dc34.png)

![1-2.png](https://p.ananas.chaoxing.com/star3/origin/9da08bd9d538f4a3e66c1dbee4441cc9.png)

![1-3.png](https://p.ananas.chaoxing.com/star3/origin/eece150ec54cc108b892f1b4e022164a.png)



# 2.(简答题)写出如下程序片段中每条算数运算指令执行后标志CF，ZF，SF，OF，PF和AF的状态，具体题目请参见教材P56 题目10

*我的答案：*

*15*分

| 运算结果 | CF   | ZF   | SF   | OF   | PF   | AF   |
| :------- | :--- | :--- | :--- | :--- | :--- | :--- |
| 89 H     | 0    | 0    | 0    | 0    | 0    | 0    |
| 12 H     | 1    | 0    | 0    | 1    | 1    | 1    |
| af H     | 0    | 0    | 1    | 0    | 1    | 0    |
| af H     | 1    | 0    | 1    | 0    | 1    | 0    |
| 0        | 0    | 1    | 0    | 0    | 1    | 0    |
| -1       | 0    | 0    | 1    | 0    | 1    | 1    |
| 0        | 0    | 1    | 0    | 0    | 1    | 1    |

*正确答案：*

![2-1.png](https://p.ananas.chaoxing.com/star3/origin/bf0b1f712b3e8510cebc0f626705b43c.png)

![2-2.png](https://p.ananas.chaoxing.com/star3/origin/1281b5b06c3e6b07ca6c6ecb484aa31e.png)

![2-3.png](https://p.ananas.chaoxing.com/star3/origin/a602eab34214430f063ac6545478f5db.png)



# 3.(简答题)简要说明如下指令中源操作数的寻址方式，并互相比较，具体内容参见教材17题

- *我的答案：**15*分

  直接寻址

  立即数寻址

  寄存器寻址

  寄存器间接寻址

  寄存器相对寻址 

- *正确答案：*

  MOV   EBX，【1234H】  直接寻址

  MOV   EBX，1234H    立即数寻址

  MOV   EDX，EBX      寄存器寻址

  MOV   EDX，【EBX】    寄存器间接寻址

  MOV   EDX，【EBX+1234H】基址寻址 



# 4. (简答题)设寄存器ECX的内容是100H，寄存器EDX的内容是1234H，请写出执行如下每条指令后，寄存器EAX的值，具体题目请参见教材23题

我的答案：

| EAX 的值               |
| ---------------------- |
| 1237 H                 |
| 800 H                  |
| 1634 H                 |
| 2563 H                 |
| 5678 H                 |
| 未知（或者是 *0x5678） |

*正确答案：*

![5-1.png](https://p.ananas.chaoxing.com/star3/origin/1e8d481d47526e7fefb6de86b8231a5a.png)

![5-2.png](https://p.ananas.chaoxing.com/star3/origin/0447ef76dde0a4cca982cba0ddc79065.png)

![5-3.png](https://p.ananas.chaoxing.com/star3/origin/fd8230fe46780a8a9d9e2bc7fdba9b23.png)





# 5.请指出下列指令的错误所在，具体请参见教材30题

- *我的答案：**15*分

  操作数长度不同

  不能与立即数交换

  300 H超过 AL 长度

  EIP不能是操作数若有两个操作数，只能有一个是存储器操作数

  PUSH 和 POP 只能处理16位操作数（8086/8080）

  操作数长度不同

  段寄存器不能作为算术运算指令的操作数

- *正确答案：*

  （1）MOV  CX，DL       两操作数尺寸不一致

  （2）XCHG  【ESI】，3      立即数3不是存储单元

  （3）MOV  AL，300       立即数300超过了8位寄存器能保存的数值范围，操作数尺寸不一致

  （4）MOV  EIP，EAX      EIP不能作为目的操作数

  （5）SUB   【ESI】，【EDI】  源操作数和目的操作数不能同时为存储器操作数

  （6）PUSH  DH          push指令操作数应为16位或32位（7）XCHG  ECX，DX      操作数尺寸不一致

  （8）CMP  AX，DS       段寄存器DS不能作为操作数，它只能指示操作数所在的段地址

  

# 6. (简答题)在VS或VC环境下，编辑运行如下控制台程序，并写出运行结果，具体题目参照教材32题

- *我的答案：**17*分

  A = 10，B = 99，C = 768