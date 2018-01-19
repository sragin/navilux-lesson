# navilux-lesson
나빌룩스 레슨(https://kldp.org/node/109762) 을 진행하면서 만든 저장소

## QEMU 시뮬레이션 환경
* machine: integratorcp
* cpu: cortex-a9
* memory: 128MB

## QEMU 실행명령
    qemu-system-arm -machine integratorcp -cpu cortex-a9 -m 128M -kernel ./final_image.elf -serial stdio
