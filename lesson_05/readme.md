# Navilux Lesson5
## QEMU 실행 후 icp_pic_read: Bad register offset 0xc 에러 메시지 출력
PIC_IRQ_ENCLR 레지스터는 쓰기 전용인데 값을 읽어서 에러발생<br>
아래와 같이 코드변경

    --- PIC_IRQ_ENCLR |= (1<<6);
    +++ PIC_IRQ_ENCLR = (1<<6);
