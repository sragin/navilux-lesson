### S/W Interrup handler 정의
Core_swiHandler를 전역변수로 등록<br>
Core_swiHandler 함수 시작

    .global Core_swiHandler
    Core_swiHandler:

### 레지스터 백업

스택에 r0-r12,r14 저장<br>
r0-12는 범용 레지스터이고 공유되는 공간이므로 백업이 필요하다.<br>
r14는 인터럽트가 걸렸을 때 pc의 값을 가지고 있으므로 인터럽트가 끝난 후 돌아갈 주소를 가지고 있다.

    PUSH    {r0-r12,r14}

SPSR을 r1에 복사

    MRS     r1,spsr
    
r1(SPSR)을 스택에 저장

    PUSH    {r1}

### Interrupt handler로 분기

C함수 swiHandler로 브랜치

    bl      swiHandler

### 레지스터 복원

위에서 저장한 모든 것을 복원<br>
복원은 백업의 역순으로 진행함<br>
<br>
스택이 마지막으로 가리키는 곳에 저장된 값을 r1에 가져옴<br>
마지막에 저장된 값은 spsr의 값이다

    POP     {r1}

r1에 저장된 spsr의 값을 다시 spsr에 저장

    msr     spsr_cxsf,r1
    
r0-r12, pc의 값을 복원. 다음 클럭에 pc가 가리키는 주소부터 fetch됨

    POP     {r0-r12,pc}
