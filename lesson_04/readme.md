Core_swiHandler를 전역변수로 등록

    .global Core_swiHandler

Core_swiHandler 함수 시작

    Core_swiHandler:
    
STACK에 r0-r12,r14 저장<br>
r0-12는 범용 레지스터이고 공유되는 공간이므로 백업이 필요하다.<br>
r14는 인터럽트가 걸렸을 때 pc의 값을 가지고 있으므로 인터럽트가 끝난 후 돌아갈 주소를 가지고 있다.

    PUSH    {r0-r12,r14}

PSR을 r1에 이동함.

    MRS     r1,spsr
    stmfd   sp!,{r1}
    bl      swiHandler
    ldmfd   sp!,{r1}
    msr     spsr_cxsf,r1
    ldmfd   sp!,{r0-r12,pc}^
