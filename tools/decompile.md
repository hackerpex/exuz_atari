
https://www.masswerk.at/6502/disassembler.html


#desassembly game
```
pip3 install py65
```
Desmontar a ROM:
```
py65mon
```
Dentro do monitor interativo:

```
load "input.bin" 0x0000
disassemble 0x0000

```