# START.S
## S/W Interrup handler 정의
software_interrupt 함수 시작

    software_interrupt:

## 레지스터 백업
스택에 r0-r12,r14 저장<br>
r0-12는 범용 레지스터이고 공유되는 공간이므로 백업이 필요하다.<br>
r14는 인터럽트가 걸렸을 때 pc의 값을 가지고 있으므로 인터럽트가 끝난 후 돌아갈 주소를 가지고 있다.

    PUSH	{r0-r12,r14}

## SWI 인자 가져오기
lr에 저장된 리턴주소는 svc명령 다음 주소이다. svc명령을 가져오기 위해서 lr에 -4를 해야 올바른 값이 추출된다.<br>
svc명령의 하위 3바이트를 and not(bit clear) 명령으로 추출한다.

    ldr     r0, [lr, #-4]
    bic     r0, r0, #0xff000000

## Interrupt handler로 분기
C함수 swiHandler로 브랜치

    bl      swiHandler

## 레지스터 복원
위에서 백업한 레지스터를 복원<br>
복원할 때 POP을 쓰지않은 이유는 POP명령은 CSPR을 동시에 복원하는 '^'인수를 사용할 수 없고 별도로 복사해야하기 때문이다.

    LDMFD   sp!,{r0-r12,pc}^

### 인수 '^'
ARM 상태에서만 사용할 수 있는 선택적 접미사로, 사용자 모드나 시스템 모드에서는 사용할 수 없습니다. 이 접미사의 용도는 다음과 같습니다.
* 명령어가 LDM (임의의 주소 지정 모드 포함) 이고 reglist 에 일반 다중 레지스터 전송 외에도 pc (r15) 가 포함되어 있는 경우 SPSR 이 CPSR 로 복사됩니다. 이는 예외 처리기에서 복귀하기 위한 것으로, 예외 모드에서만 사용해야 합니다.
* 또는 현재 모드 레지스터 대신 사용자 모드 레지스터 내부 또는 외부로 데이터를 전송합니다.

※ 문서번호: DUI0204IK, RealView Compilation Tools 버전 4.0 어셈블러 설명서 4-28페이지 참조.

# MAIN.C

## SWI Handler
어떤 시스템 콜이 불렸는지 그 번호를 출력함.

    void swiHandler(unsigned int syscallnum)
    {
        char strTmp[100];
        sprintf(strTmp, "system call %d\n", syscallnum);
        my_puts(strTmp);
    }


## SWI Caller (main)
1초에 한 번 SVC(예전의 SWI) 명령을 실행한다. 인자로 77을 넘김<br>
77은 magic number임. 강좌를 따라한 것이고 특별한 의미없음

    int main (void)
    {
        while(1)
        {
            __asm__("svc 77");
            msleep(1000);
        }

        return 0;
    }
