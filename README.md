# STM32F103RB-playground
Bare-metal stuff with STM32 and libopencm3 on NixOS using ST-Link

## Prereqs

If you want to replicate this yourself without cloning my repo, please use below commands to use libopencm3

```bash
git submodule add https://github.com/libopencm3/libopencm3.git libopencm3
```

Then run below command, and substitute with your STM32 (I use the STM32F103RB for this project).

```bash
cd libopencm3
make TARGETS=stm32/f1
```
