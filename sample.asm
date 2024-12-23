                            * = $D878
D878   D8                   CLD
D879   78                   SEI
D87A   A2 FF                LDX #$FF
D87C   9A                   TXS
D87D   E8                   INX
D87E   8A                   TXA
D87F   95 00      LD87F     STA $00,X
D881   E8                   INX
D882   D0 FB                BNE LD87F
D884   A9 06                LDA #$06
D886   85 84                STA $84
D888   0A                   ASL A
D889   85 EC                STA $EC
D88B   CA                   DEX
D88C   86 82                STX $82
D88E   86 CB                STX $CB
D890   20 F4 FB             JSR $FBF4
D893   A9 CB                LDA #$CB
D895   85 CC                STA $CC
D897   4A                   LSR A
D898   85 B6                STA $B6
D89A   A9 ED                LDA #$ED
D89C   85 CE                STA $CE
D89E   A9 0F                LDA #$0F
D8A0   85 D0                STA $D0
D8A2   A2 04                LDX #$04
D8A4   95 C0      LD8A4     STA $C0,X
D8A6   CA                   DEX
D8A7   D0 FB                BNE LD8A4
D8A9   85 02                STA $02
D8AB   A9 F0                LDA #$F0
D8AD   85 23                STA $23
D8AF   A9 80                LDA #$80
D8B1   85 24                STA $24
D8B3   A2 06                LDX #$06
D8B5   CA         LD8B5     DEX
D8B6   D0 FD                BNE LD8B5
D8B8   85 14                STA $14
D8BA   85 13                STA $13
D8BC   85 02                STA $02
D8BE   85 2A                STA $2A
D8C0   85 02                STA $02
D8C2   85 2B                STA $2B
D8C4   86 E7                STX $E7
D8C6   86 98                STX $98
D8C8   4C D6 F7             JMP $F7D6
D8CB   A9 00                LDA #$00
D8CD   E4 D9                CPX $D9
D8CF   30 09                BMI LD8DA
D8D1   A4 DC                LDY $DC
D8D3   30 05                BMI LD8DA
D8D5   B1 DF                LDA ($DF),Y
D8D7   88                   DEY
D8D8   84 DC                STY $DC
D8DA   85 02      LD8DA     STA $02
D8DC   85 1C                STA $1C
D8DE   60                   RTS
D8DF   20 53 F0             JSR $F053
D8E2   A9 00                LDA #$00
D8E4   E8                   INX
D8E5   E4 D8                CPX $D8
D8E7   30 09                BMI LD8F2
D8E9   A4 DB                LDY $DB
D8EB   30 05                BMI LD8F2
D8ED   B1 DD                LDA ($DD),Y
D8EF   88                   DEY
D8F0   84 DB                STY $DB
D8F2   85 02      LD8F2     STA $02
D8F4   85 1B                STA $1B
D8F6   60                   RTS
D8F7   85 02                STA $02
D8F9   A9 20                LDA #$20
D8FB   85 04                STA $04
D8FD   A2 00                LDX #$00
D8FF   A8                   TAY
D900   A5 80                LDA $80
D902   29 08                AND #$08
D904   D0 03                BNE LD909
D906   A2 09                LDX #$09
D908   EA                   NOP
D909   CA         LD909     DEX
D90A   10 FD                BPL LD909
D90C   85 12                STA $12
D90E   84 22                STY $22
D910   84 05                STY $05
D912   A2 01                LDX #$01
D914   A9 01      LD914     LDA #$01
D916   18                   CLC
D917   75 B0                ADC $B0,X
D919   A0 02                LDY #$02
D91B   38                   SEC
D91C   C8         LD91C     INY
D91D   E9 0F                SBC #$0F
D91F   B0 FB                BCS LD91C
D921   49 FF                EOR #$FF
D923   E9 06                SBC #$06
D925   0A                   ASL A
D926   0A                   ASL A
D927   0A                   ASL A
D928   0A                   ASL A
D929   85 02                STA $02
D92B   88         LD92B     DEY
D92C   10 FD                BPL LD92B
D92E   95 10                STA $10,X
D930   95 20                STA $20,X
D932   CA                   DEX
D933   10 DF                BPL LD914
D935   85 02                STA $02
D937   85 2A                STA $2A
D939   A0 01                LDY #$01
D93B   A2 07                LDX #$07
D93D   AD 84 02   LD93D     LDA $0284
D940   D0 FB                BNE LD93D
D942   85 02                STA $02
D944   84 01                STY $01
D946   85 2B                STA $2B
D948   A5 F0                LDA $F0
D94A   85 09                STA $09
D94C   84 CA                STY $CA
D94E   88                   DEY
D94F   84 87                STY $87
D951   86 C9                STX $C9
D953   E8                   INX
D954   A9 31                LDA #$31
D956   85 0A                STA $0A
D958   A5 F1                LDA $F1
D95A   85 08                STA $08
D95C   20 6A F0             JSR $F06A
D95F   A0 FF                LDY #$FF
D961   84 0D                STY $0D
D963   84 0E                STY $0E
D965   A9 7F                LDA #$7F
D967   85 0F                STA $0F
D969   4C 13 F3             JMP $F313
D96C   A9 00                LDA #$00
D96E   E4 D9                CPX $D9
D970   30 09                BMI LD97B
D972   A4 DC                LDY $DC
D974   30 05                BMI LD97B
D976   B1 DF                LDA ($DF),Y
D978   88                   DEY
D979   84 DC                STY $DC
D97B   85 02      LD97B     STA $02
D97D   85 1C                STA $1C
D97F   A4 CA                LDY $CA
D981   88                   DEY
D982   F0 6A                BEQ LD9EE
D984   A4 87                LDY $87
D986   B9 88 00             LDA $0088,Y
D989   29 0F                AND #$0F
D98B   A8                   TAY
D98C   B9 47 FD             LDA $FD47,Y
D98F   85 D4                STA $D4
D991   20 6A F0             JSR $F06A
D994   A9 00                LDA #$00
D996   85 1D                STA $1D
D998   A4 87                LDY $87
D99A   B9 88 00             LDA $0088,Y
D99D   4A                   LSR A
D99E   4A                   LSR A
D99F   4A                   LSR A
D9A0   4A                   LSR A
D9A1   29 07                AND #$07
D9A3   A8                   TAY
D9A4   B9 3F FD             LDA $FD3F,Y
D9A7   85 D3                STA $D3
D9A9   20 53 F0             JSR $F053
D9AC   A4 87                LDY $87
D9AE   B9 88 00             LDA $0088,Y
D9B1   10 04                BPL LD9B7
D9B3   A9 50                LDA #$50
D9B5   D0 02                BNE LD9B9
D9B7   A9 10      LD9B7     LDA #$10
D9B9   85 D2      LD9B9     STA $D2
D9BB   B9 8C 00             LDA $008C,Y
D9BE   29 07                AND #$07
D9C0   A8                   TAY
D9C1   B9 63 FD             LDA $FD63,Y
D9C4   85 D7                STA $D7
D9C6   20 6A F0             JSR $F06A
D9C9   A4 87                LDY $87
D9CB   B9 8C 00             LDA $008C,Y
D9CE   4A                   LSR A
D9CF   4A                   LSR A
D9D0   4A                   LSR A
D9D1   85 D5                STA $D5
D9D3   29 07                AND #$07
D9D5   A8                   TAY
D9D6   B9 5B FD             LDA $FD5B,Y
D9D9   85 D6                STA $D6
D9DB   20 53 F0             JSR $F053
D9DE   A5 D5                LDA $D5
D9E0   4A                   LSR A
D9E1   4A                   LSR A
D9E2   4A                   LSR A
D9E3   29 03                AND #$03
D9E5   A8                   TAY
D9E6   B9 57 FD             LDA $FD57,Y
D9E9   85 D5                STA $D5
D9EB   4C F4 F1             JMP $F1F4
D9EE   A4 87      LD9EE     LDY $87
D9F0   B9 90 00             LDA $0090,Y
D9F3   29 07                AND #$07
D9F5   A8                   TAY
D9F6   B9 7B FD             LDA $FD7B,Y
D9F9   85 D4                STA $D4
D9FB   20 6A F0             JSR $F06A
D9FE   A9 00                LDA #$00
DA00   85 1D                STA $1D
DA02   A5 E1                LDA $E1
DA04   85 1F                STA $1F
DA06   A4 87                LDY $87
DA08   B9 90 00             LDA $0090,Y
DA0B   4A                   LSR A
DA0C   4A                   LSR A
DA0D   4A                   LSR A
DA0E   29 0F                AND #$0F
DA10   A8                   TAY
DA11   B9 6B FD             LDA $FD6B,Y
DA14   85 D3                STA $D3
DA16   20 53 F0             JSR $F053
DA19   A4 87                LDY $87
DA1B   B9 90 00             LDA $0090,Y
DA1E   10 04                BPL LDA24
DA20   A9 50                LDA #$50
DA22   D0 02                BNE LDA26
DA24   A9 10      LDA24     LDA #$10
DA26   85 D2      LDA26     STA $D2
DA28   B9 94 00             LDA $0094,Y
DA2B   29 07                AND #$07
DA2D   A8                   TAY
DA2E   B9 63 FD             LDA $FD63,Y
DA31   85 D7                STA $D7
DA33   20 6A F0             JSR $F06A
DA36   A4 87                LDY $87
DA38   B9 94 00             LDA $0094,Y
DA3B   4A                   LSR A
DA3C   4A                   LSR A
DA3D   4A                   LSR A
DA3E   85 D5                STA $D5
DA40   29 07                AND #$07
DA42   A8                   TAY
DA43   B9 83 FD             LDA $FD83,Y
DA46   85 D6                STA $D6
DA48   20 53 F0             JSR $F053
DA4B   A5 E1                LDA $E1
DA4D   85 1E                STA $1E
DA4F   A5 D5                LDA $D5
DA51   4A                   LSR A
DA52   4A                   LSR A
DA53   4A                   LSR A
DA54   A8                   TAY
DA55   B9 47 FD             LDA $FD47,Y
DA58   85 D5                STA $D5
DA5A   4C F4 F1             JMP $F1F4
DA5D   A5 D6      LDA5D     LDA $D6
DA5F   85 0E                STA $0E
DA61   EA                   NOP
DA62   EA                   NOP
DA63   A5 D7      LDA63     LDA $D7
DA65   85 0F                STA $0F
DA67   A9 00                LDA #$00
DA69   4C 46 F2             JMP $F246
DA6C   20 6A F0             JSR $F06A
DA6F   A5 C9                LDA $C9
DA71   C9 04                CMP #$04
DA73   D0 0C                BNE LDA81
DA75   A9 40                LDA #$40
DA77   05 D4                ORA $D4
DA79   85 D4                STA $D4
DA7B   A9 20                LDA #$20
DA7D   05 D5                ORA $D5
DA7F   85 D5                STA $D5
DA81   A9 00      LDA81     LDA #$00
DA83   E4 D9                CPX $D9
DA85   30 09                BMI LDA90
DA87   A4 DC                LDY $DC
DA89   30 05                BMI LDA90
DA8B   B1 DF                LDA ($DF),Y
DA8D   88                   DEY
DA8E   84 DC                STY $DC
DA90   85 02      LDA90     STA $02
DA92   85 1C                STA $1C
DA94   A5 D2                LDA $D2
DA96   85 0D                STA $0D
DA98   A0 30                LDY #$30
DA9A   84 0A                STY $0A
DA9C   A5 D3                LDA $D3
DA9E   85 0E                STA $0E
DAA0   A5 D4                LDA $D4
DAA2   85 0F                STA $0F
DAA4   E8                   INX
DAA5   A5 D5                LDA $D5
DAA7   85 0D                STA $0D
DAA9   E4 D8                CPX $D8
DAAB   30 B0                BMI LDA5D
DAAD   A5 D6                LDA $D6
DAAF   85 0E                STA $0E
DAB1   A4 DB                LDY $DB
DAB3   30 AE                BMI LDA63
DAB5   A5 D7                LDA $D7
DAB7   85 0F                STA $0F
DAB9   B1 DD                LDA ($DD),Y
DABB   88                   DEY
DABC   84 DB                STY $DB
DABE   85 02                STA $02
DAC0   85 1B                STA $1B
DAC2   A5 D2                LDA $D2
DAC4   85 0D                STA $0D
DAC6   A5 D3                LDA $D3
DAC8   85 0E                STA $0E
DACA   A5 D4                LDA $D4
DACC   85 0F                STA $0F
DACE   EA                   NOP
DACF   EA                   NOP
DAD0   A5 D5                LDA $D5
DAD2   85 0D                STA $0D
DAD4   E4 D9                CPX $D9
DAD6   30 18                BMI LDAF0
DAD8   A5 D6                LDA $D6
DADA   85 0E                STA $0E
DADC   A4 DC                LDY $DC
DADE   30 16                BMI LDAF6
DAE0   A5 D7                LDA $D7
DAE2   85 0F                STA $0F
DAE4   B1 DF                LDA ($DF),Y
DAE6   88                   DEY
DAE7   84 DC                STY $DC
DAE9   85 02                STA $02
DAEB   85 1C                STA $1C
DAED   4C 87 F2             JMP $F287
DAF0   A5 D6      LDAF0     LDA $D6
DAF2   85 0E                STA $0E
DAF4   EA                   NOP
DAF5   EA                   NOP
DAF6   A5 D7      LDAF6     LDA $D7
DAF8   85 0F                STA $0F
DAFA   A9 00                LDA #$00
DAFC   4C 71 F2             JMP $F271
DAFF   A4 CA                LDY $CA
DB01   B9 0A FE             LDA $FE0A,Y
DB04   85 0D                STA $0D
DB06   B9 0C FE             LDA $FE0C,Y
DB09   85 0E                STA $0E
DB0B   A9 31                LDA #$31
DB0D   85 0A                STA $0A
DB0F   A5 E3                LDA $E3
DB11   85 0F                STA $0F
DB13   A5 C9                LDA $C9
DB15   18                   CLC
DB16   69 FF                ADC #$FF
DB18   10 03                BPL LDB1D
DB1A   4C 60 F3             JMP $F360
DB1D   85 C9      LDB1D     STA $C9
DB1F   A9 00                LDA #$00
DB21   E8                   INX
DB22   E4 D8                CPX $D8
DB24   30 09                BMI LDB2F
DB26   A4 DB                LDY $DB
DB28   30 05                BMI LDB2F
DB2A   B1 DD                LDA ($DD),Y
DB2C   88                   DEY
DB2D   84 DB                STY $DB
DB2F   85 02      LDB2F     STA $02
DB31   85 1B                STA $1B
DB33   A0 00                LDY #$00
DB35   84 1E                STY $1E
DB37   84 E2                STY $E2
DB39   A5 C9                LDA $C9
DB3B   A8                   TAY
DB3C   29 01                AND #$01
DB3E   85 CA                STA $CA
DB40   C8                   INY
DB41   98                   TYA
DB42   4A                   LSR A
DB43   85 87                STA $87
DB45   20 67 F0             JSR $F067
DB48   A0 01                LDY #$01
DB4A   A5 80                LDA $80
DB4C   29 08                AND #$08
DB4E   D0 02                BNE LDB52
DB50   A0 03                LDY #$03
DB52   A5 C9      LDB52     LDA $C9
DB54   F0 05                BEQ LDB5B
DB56   C9 06                CMP #$06
DB58   D0 0C                BNE LDB66
DB5A   88                   DEY
DB5B   A5 9A      LDB5B     LDA $9A
DB5D   39 6C FE             AND $FE6C,Y
DB60   F0 04                BEQ LDB66
DB62   A9 02                LDA #$02
DB64   85 E2                STA $E2
DB66   20 53 F0   LDB66     JSR $F053
DB69   A9 00                LDA #$00
DB6B   85 1F                STA $1F
DB6D   20 6A F0             JSR $F06A
DB70   A5 E2                LDA $E2
DB72   85 1D                STA $1D
DB74   20 53 F0             JSR $F053
DB77   20 6A F0             JSR $F06A
DB7A   A4 CA                LDY $CA
DB7C   B9 41 FF             LDA $FF41,Y
DB7F   85 0D                STA $0D
DB81   B9 0F FE             LDA $FE0F,Y
DB84   85 0E                STA $0E
DB86   B9 11 FE             LDA $FE11,Y
DB89   85 0F                STA $0F
DB8B   20 53 F0             JSR $F053
DB8E   A5 E7                LDA $E7
DB90   A4 C9                LDY $C9
DB92   C0 03                CPY #$03
DB94   F0 02                BEQ LDB98
DB96   A9 00                LDA #$00
DB98   85 E1      LDB98     STA $E1
DB9A   20 6A F0             JSR $F06A
DB9D   A4 CA                LDY $CA
DB9F   B9 0D FE             LDA $FE0D,Y
DBA2   A4 C9                LDY $C9
DBA4   C0 04                CPY #$04
DBA6   D0 02                BNE LDBAA
DBA8   A9 40                LDA #$40
DBAA   85 E3      LDBAA     STA $E3
DBAC   20 53 F0             JSR $F053
DBAF   A9 00                LDA #$00
DBB1   E8                   INX
DBB2   E4 D8                CPX $D8
DBB4   30 09                BMI LDBBF
DBB6   A4 DB                LDY $DB
DBB8   30 05                BMI LDBBF
DBBA   B1 DD                LDA ($DD),Y
DBBC   88                   DEY
DBBD   84 DB                STY $DB
DBBF   85 02      LDBBF     STA $02
DBC1   85 1B                STA $1B
DBC3   A4 CA                LDY $CA
DBC5   85 1B                STA $1B
DBC7   B9 0A FE             LDA $FE0A,Y
DBCA   85 0D                STA $0D
DBCC   B9 0C FE             LDA $FE0C,Y
DBCF   85 0E                STA $0E
DBD1   A5 E3                LDA $E3
DBD3   85 0F                STA $0F
DBD5   4C F4 F0             JMP $F0F4
DBD8   A9 00                LDA #$00
DBDA   E8                   INX
DBDB   E4 D8                CPX $D8
DBDD   30 09                BMI LDBE8
DBDF   A4 DB                LDY $DB
DBE1   30 05                BMI LDBE8
DBE3   B1 DD                LDA ($DD),Y
DBE5   88                   DEY
DBE6   84 DB                STY $DB
DBE8   85 02      LDBE8     STA $02
DBEA   85 1B                STA $1B
DBEC   20 67 F0             JSR $F067
DBEF   20 67 F0             JSR $F067
DBF2   20 67 F0             JSR $F067
DBF5   A9 FF                LDA #$FF
DBF7   85 0D                STA $0D
DBF9   85 0E                STA $0E
DBFB   A9 7F                LDA #$7F
DBFD   85 0F                STA $0F
DBFF   A9 4C                LDA #$4C
DC01   8D 96 02             STA $0296
DC04   20 53 F0             JSR $F053
DC07   20 6A F0             JSR $F06A
DC0A   20 53 F0             JSR $F053
DC0D   A9 03                LDA #$03
DC0F   A0 00                LDY #$00
DC11   85 02                STA $02
DC13   84 0D                STY $0D
DC15   84 0E                STY $0E
DC17   84 0F                STY $0F
DC19   84 0C                STY $0C
DC1B   85 04                STA $04
DC1D   85 05                STA $05
DC1F   85 25                STA $25
DC21   85 26                STA $26
DC23   20 83 F4             JSR $F483
DC26   A5 82                LDA $82
DC28   85 07                STA $07
DC2A   85 06                STA $06
DC2C   A2 07                LDX #$07
DC2E   85 02                STA $02
DC30   CA         LDC30     DEX
DC31   D0 FD                BNE LDC30
DC33   EA                   NOP
DC34   85 10                STA $10
DC36   85 11                STA $11
DC38   A9 F0                LDA #$F0
DC3A   85 20                STA $20
DC3C   85 02                STA $02
DC3E   85 2A                STA $2A
DC40   86 09                STX $09
DC42   A0 04                LDY #$04
DC44   A5 F5                LDA $F5
DC46   85 D2                STA $D2
DC48   20 EE F3             JSR $F3EE
DC4B   A5 E6                LDA $E6
DC4D   0A                   ASL A
DC4E   10 09                BPL LDC59
DC50   A0 05                LDY #$05
DC52   A5 F4                LDA $F4
DC54   85 D2                STA $D2
DC56   20 EE F3             JSR $F3EE
DC59   A9 00      LDC59     LDA #$00
DC5B   85 25                STA $25
DC5D   85 26                STA $26
DC5F   85 04                STA $04
DC61   85 05                STA $05
DC63   4C 8E F4             JMP $F48E
DC66   A2 08                LDX #$08
DC68   A9 00                LDA #$00
DC6A   85 E1                STA $E1
DC6C   F0 2C                BEQ LDC9A
DC6E   B9 CC 00   LDC6E     LDA $00CC,Y
DC71   4A                   LSR A
DC72   4A                   LSR A
DC73   4A                   LSR A
DC74   4A                   LSR A
DC75   AA                   TAX
DC76   F0 02                BEQ LDC7A
DC78   E6 E1                INC $E1
DC7A   A5 E1      LDC7A     LDA $E1
DC7C   D0 02                BNE LDC80
DC7E   A2 0A                LDX #$0A
DC80   BD F6 FE   LDC80     LDA $FEF6,X
DC83   A6 E2                LDX $E2
DC85   95 D5                STA $D5,X
DC87   CA                   DEX
DC88   CA                   DEX
DC89   E0 04                CPX #$04
DC8B   D0 04                BNE LDC91
DC8D   A9 00                LDA #$00
DC8F   F0 05                BEQ LDC96
DC91   8A         LDC91     TXA
DC92   D0 06                BNE LDC9A
DC94   A5 D2                LDA $D2
DC96   85 02      LDC96     STA $02
DC98   85 09                STA $09
DC9A   86 E2      LDC9A     STX $E2
DC9C   B9 CC 00             LDA $00CC,Y
DC9F   29 0F                AND #$0F
DCA1   AA                   TAX
DCA2   F0 02                BEQ LDCA6
DCA4   E6 E1                INC $E1
DCA6   A5 E1      LDCA6     LDA $E1
DCA8   D0 02                BNE LDCAC
DCAA   A2 0A                LDX #$0A
DCAC   BD F6 FE   LDCAC     LDA $FEF6,X
DCAF   A6 E2                LDX $E2
DCB1   95 D5                STA $D5,X
DCB3   CA                   DEX
DCB4   CA                   DEX
DCB5   86 E2                STX $E2
DCB7   88                   DEY
DCB8   88                   DEY
DCB9   10 B3                BPL LDC6E
DCBB   A5 E1                LDA $E1
DCBD   D0 04                BNE LDCC3
DCBF   A9 AC                LDA #$AC
DCC1   85 D5                STA $D5
DCC3   A9 FE      LDCC3     LDA #$FE
DCC5   A2 09                LDX #$09
DCC7   95 D5      LDCC7     STA $D5,X
DCC9   CA                   DEX
DCCA   CA                   DEX
DCCB   10 FA                BPL LDCC7
DCCD   A9 06                LDA #$06
DCCF   85 E1                STA $E1
DCD1   A4 E1      LDCD1     LDY $E1
DCD3   A9 00                LDA #$00
DCD5   85 1B                STA $1B
DCD7   85 1B                STA $1B
DCD9   85 02                STA $02
DCDB   B1 DD                LDA ($DD),Y
DCDD   85 1C                STA $1C
DCDF   B1 DB                LDA ($DB),Y
DCE1   85 1B                STA $1B
DCE3   B1 D9                LDA ($D9),Y
DCE5   85 E2                STA $E2
DCE7   B1 D7                LDA ($D7),Y
DCE9   AA                   TAX
DCEA   B1 D5                LDA ($D5),Y
DCEC   A8                   TAY
DCED   A5 E2                LDA $E2
DCEF   85 1C                STA $1C
DCF1   86 1B                STX $1B
DCF3   84 1C                STY $1C
DCF5   84 1B                STY $1B
DCF7   C6 E1                DEC $E1
DCF9   10 D6                BPL LDCD1
DCFB   A9 00                LDA #$00
DCFD   85 1B                STA $1B
DCFF   85 1C                STA $1C
DD01   85 1B                STA $1B
DD03   85 1C                STA $1C
DD05   60                   RTS
DD06   A8                   TAY
DD07   A5 E6                LDA $E6
DD09   10 02                BPL LDD0D
DD0B   A0 03                LDY #$03
DD0D   A6 98      LDD0D     LDX $98
DD0F   20 68 FC             JSR $FC68
DD12   A9 00                LDA #$00
DD14   85 02                STA $02
DD16   85 09                STA $09
DD18   A0 03                LDY #$03
DD1A   A5 E6                LDA $E6
DD1C   10 02                BPL LDD20
DD1E   A0 00                LDY #$00
DD20   A6 AC      LDD20     LDX $AC
DD22   20 68 FC             JSR $FC68
DD25   A2 06                LDX #$06
DD27   A5 F4                LDA $F4
DD29   85 07                STA $07
DD2B   A5 F5                LDA $F5
DD2D   85 06                STA $06
DD2F   85 02      LDD2F     STA $02
DD31   A9 02                LDA #$02
DD33   85 0A                STA $0A
DD35   A5 D2                LDA $D2
DD37   85 0D                STA $0D
DD39   A5 D3                LDA $D3
DD3B   85 0E                STA $0E
DD3D   A5 D4                LDA $D4
DD3F   85 0F                STA $0F
DD41   EA                   NOP
DD42   EA                   NOP
DD43   EA                   NOP
DD44   A5 D5                LDA $D5
DD46   85 0D                STA $0D
DD48   A5 D6                LDA $D6
DD4A   85 0E                STA $0E
DD4C   A5 D7                LDA $D7
DD4E   85 0F                STA $0F
DD50   CA                   DEX
DD51   D0 DC                BNE LDD2F
DD53   85 02                STA $02
DD55   86 0A                STX $0A
DD57   86 08                STX $08
DD59   86 0D                STX $0D
DD5B   86 0E                STX $0E
DD5D   86 0F                STX $0F
DD5F   A6 82                LDX $82
DD61   D0 09                BNE LDD6C
DD63   20 AD FB             JSR $FBAD
DD66   A5 E5                LDA $E5
DD68   10 05                BPL LDD6F
DD6A   C6 E5                DEC $E5
DD6C   4C C3 F7   LDD6C     JMP $F7C3
DD6F   A5 E4      LDD6F     LDA $E4
DD71   F0 60                BEQ LDDD3
DD73   A5 80                LDA $80
DD75   6A                   ROR A
DD76   90 5B                BCC LDDD3
DD78   C6 E4                DEC $E4
DD7A   D0 57                BNE LDDD3
DD7C   24 9A                BIT $9A
DD7E   A5 9A                LDA $9A
DD80   10 10                BPL LDD92
DD82   50 0A                BVC LDD8E
DD84   29 BF                AND #$BF
DD86   85 9A                STA $9A
DD88   A9 20                LDA #$20
DD8A   85 E4                STA $E4
DD8C   10 45                BPL LDDD3
DD8E   29 7C      LDD8E     AND #$7C
DD90   85 9A                STA $9A
DD92   A5 E7      LDD92     LDA $E7
DD94   29 40                AND #$40
DD96   F0 33                BEQ LDDCB
DD98   45 E7                EOR $E7
DD9A   85 E7                STA $E7
DD9C   20 21 FC             JSR $FC21
DD9F   24 E6                BIT $E6
DDA1   50 0D                BVC LDDB0
DDA3   A5 AC                LDA $AC
DDA5   F0 09                BEQ LDDB0
DDA7   20 9F FB             JSR $FB9F
DDAA   A5 E6                LDA $E6
DDAC   49 80                EOR #$80
DDAE   85 E6                STA $E6
DDB0   A5 98      LDDB0     LDA $98
DDB2   05 AC                ORA $AC
DDB4   F0 0A                BEQ LDDC0
DDB6   C6 98                DEC $98
DDB8   A9 08                LDA #$08
DDBA   05 E7                ORA $E7
DDBC   85 E7                STA $E7
DDBE   D0 13                BNE LDDD3
DDC0   85 E7      LDDC0     STA $E7
DDC2   A9 5F                LDA #$5F
DDC4   85 82                STA $82
DDC6   85 B6                STA $B6
DDC8   4C C3 F7             JMP $F7C3
DDCB   A5 E7      LDDCB     LDA $E7
DDCD   10 04                BPL LDDD3
DDCF   29 7F                AND #$7F
DDD1   85 E7                STA $E7
DDD3   A5 E7      LDDD3     LDA $E7
DDD5   10 14                BPL LDDEB
DDD7   A5 99                LDA $99
DDD9   A8                   TAY
DDDA   88                   DEY
DDDB   A2 04                LDX #$04
DDDD   95 C0      LDDDD     STA $C0,X
DDDF   94 C4                STY $C4,X
DDE1   CA                   DEX
DDE2   94 C4                STY $C4,X
DDE4   94 C0                STY $C0,X
DDE6   CA                   DEX
DDE7   D0 F4                BNE LDDDD
DDE9   F0 81                BEQ LDD6C
DDEB   A5 31      LDDEB     LDA $31
DDED   25 33                AND $33
DDEF   29 40                AND #$40
DDF1   F0 16                BEQ LDE09
DDF3   A0 06                LDY #$06
DDF5   20 45 FC             JSR $FC45
DDF8   A0 01                LDY #$01
DDFA   20 43 FF             JSR $FF43
DDFD   A5 E7                LDA $E7
DDFF   49 02                EOR #$02
DE01   85 E7                STA $E7
DE03   A9 12                LDA #$12
DE05   85 EC                STA $EC
DE07   D0 42                BNE LDE4B
DE09   AA         LDE09     TAX
DE0A   A5 B6                LDA $B6
DE0C   C9 05                CMP #$05
DE0E   F0 05                BEQ LDE15
DE10   C9 41                CMP #$41
DE12   D0 37                BNE LDE4B
DE14   E8                   INX
DE15   A5 B1      LDE15     LDA $B1
DE17   C9 04                CMP #$04
DE19   F0 06                BEQ LDE21
DE1B   C9 94                CMP #$94
DE1D   D0 2C                BNE LDE4B
DE1F   E8                   INX
DE20   E8                   INX
DE21   BD 6C FE   LDE21     LDA $FE6C,X
DE24   A8                   TAY
DE25   25 9A                AND $9A
DE27   F0 22                BEQ LDE4B
DE29   98                   TYA
DE2A   49 FF                EOR #$FF
DE2C   25 9A                AND $9A
DE2E   09 C0                ORA #$C0
DE30   85 9A                STA $9A
DE32   A0 A0                LDY #$A0
DE34   A5 E7                LDA $E7
DE36   29 20                AND #$20
DE38   F0 02                BEQ LDE3C
DE3A   A0 50                LDY #$50
DE3C   84 E4      LDE3C     STY $E4
DE3E   A0 05                LDY #$05
DE40   20 45 FC             JSR $FC45
DE43   A0 02                LDY #$02
DE45   20 43 FF             JSR $FF43
DE48   4C AA F6             JMP $F6AA
DE4B   A5 80      LDE4B     LDA $80
DE4D   29 04                AND #$04
DE4F   D0 45                BNE LDE96
DE51   A5 37                LDA $37
DE53   10 41                BPL LDE96
DE55   A5 80                LDA $80
DE57   29 03                AND #$03
DE59   AA                   TAX
DE5A   A5 9A                LDA $9A
DE5C   10 25                BPL LDE83
DE5E   B5 BC                LDA $BC,X
DE60   29 08                AND #$08
DE62   D0 32                BNE LDE96
DE64   B5 BC                LDA $BC,X
DE66   09 08                ORA #$08
DE68   95 BC                STA $BC,X
DE6A   A5 9A                LDA $9A
DE6C   29 03                AND #$03
DE6E   A8                   TAY
DE6F   20 45 FC             JSR $FC45
DE72   C0 03                CPY #$03
DE74   F0 02                BEQ LDE78
DE76   E6 9A                INC $9A
DE78   A0 03      LDE78     LDY #$03
DE7A   20 43 FF             JSR $FF43
DE7D   A9 9F                LDA #$9F
DE7F   85 E5                STA $E5
DE81   D0 13                BNE LDE96
DE83   B5 BC      LDE83     LDA $BC,X
DE85   29 08                AND #$08
DE87   D0 0D                BNE LDE96
DE89   A9 C0                LDA #$C0
DE8B   05 E7                ORA $E7
DE8D   85 E7                STA $E7
DE8F   A9 3F                LDA #$3F
DE91   85 E4                STA $E4
DE93   4C BA F7             JMP $F7BA
DE96   AD 80 02   LDE96     LDA $0280
DE99   A4 E6                LDY $E6
DE9B   30 04                BMI LDEA1
DE9D   4A                   LSR A
DE9E   4A                   LSR A
DE9F   4A                   LSR A
DEA0   4A                   LSR A
DEA1   49 FF      LDEA1     EOR #$FF
DEA3   29 0F                AND #$0F
DEA5   85 ED                STA $ED
DEA7   F0 04                BEQ LDEAD
DEA9   A9 00                LDA #$00
DEAB   85 81                STA $81
DEAD   A5 BB      LDEAD     LDA $BB
DEAF   29 20                AND #$20
DEB1   F0 2B                BEQ LDEDE
DEB3   A5 ED                LDA $ED
DEB5   4A                   LSR A
DEB6   90 1D                BCC LDED5
DEB8   A5 BB                LDA $BB
DEBA   30 12                BMI LDECE
DEBC   29 10      LDEBC     AND #$10
DEBE   D0 11                BNE LDED1
DEC0   A9 3F                LDA #$3F
DEC2   45 B6                EOR $B6
DEC4   29 3F                AND #$3F
DEC6   85 B6                STA $B6
DEC8   A9 C0                LDA #$C0
DECA   45 BB      LDECA     EOR $BB
DECC   85 BB                STA $BB
DECE   4C BA F7   LDECE     JMP $F7BA
DED1   A9 80      LDED1     LDA #$80
DED3   D0 F5                BNE LDECA
DED5   4A         LDED5     LSR A
DED6   90 F6                BCC LDECE
DED8   A5 BB                LDA $BB
DEDA   30 E0                BMI LDEBC
DEDC   10 F0                BPL LDECE
DEDE   A5 85      LDEDE     LDA $85
DEE0   D0 40                BNE LDF22
DEE2   A4 87                LDY $87
DEE4   B9 13 FE             LDA $FE13,Y
DEE7   A6 B1                LDX $B1
DEE9   E0 4C                CPX #$4C
DEEB   F0 08                BEQ LDEF5
DEED   A6 BB                LDX $BB
DEEF   10 04                BPL LDEF5
DEF1   C8                   INY
DEF2   19 13 FE             ORA $FE13,Y
DEF5   4A         LDEF5     LSR A
DEF6   90 2A                BCC LDF22
DEF8   4A                   LSR A
DEF9   AA                   TAX
DEFA   A5 C9                LDA $C9
DEFC   2A                   ROL A
DEFD   A8                   TAY
DEFE   B9 79 FE             LDA $FE79,Y
DF01   A8                   TAY
DF02   8A                   TXA
DF03   29 07                AND #$07
DF05   AA                   TAX
DF06   BD 6A FE             LDA $FE6A,X
DF09   AA                   TAX
DF0A   39 88 00             AND $0088,Y
DF0D   F0 13                BEQ LDF22
DF0F   8A                   TXA
DF10   49 FF                EOR #$FF
DF12   39 88 00             AND $0088,Y
DF15   99 88 00             STA $0088,Y
DF18   A0 04                LDY #$04
DF1A   20 45 FC             JSR $FC45
DF1D   A0 00                LDY #$00
DF1F   20 43 FF             JSR $FF43
DF22   A2 0F      LDF22     LDX #$0F
DF24   A5 9A                LDA $9A
DF26   29 3C                AND #$3C
DF28   15 88      LDF28     ORA $88,X
DF2A   CA                   DEX
DF2B   10 FB                BPL LDF28
DF2D   AA                   TAX
DF2E   D0 16                BNE LDF46
DF30   A5 98                LDA $98
DF32   C9 09                CMP #$09
DF34   F0 02                BEQ LDF38
DF36   E6 98                INC $98
DF38   A5 99      LDF38     LDA $99
DF3A   C9 0E                CMP #$0E
DF3C   F0 02                BEQ LDF40
DF3E   E6 99                INC $99
DF40   20 0C FC   LDF40     JSR $FC0C
DF43   4C BA F7             JMP $F7BA
DF46   A2 00      LDF46     LDX #$00
DF48   A5 ED                LDA $ED
DF4A   85 D2                STA $D2
DF4C   D0 03                BNE LDF51
DF4E   4C 8A F7             JMP $F78A
DF51   A4 BB      LDF51     LDY $BB
DF53   10 50                BPL $DFA5
DF55   4A                   LSR A
DF56   4A                   LSR A
DF57   29 03                AND #$03
DF59   F0 42                BEQ $DF9D
DF5B   4A                   LSR A
DF5C   A5 85                LDA $85
DF5E   D0 3D                BNE $DF9D
DF60   A5 86                LDA $86
DF62   F0 04                BEQ LDF68
DF64   90 2D                BCC $DF93
DF66   B0 10                BCS $DF78
DF68   A4 87      LDF68     LDY $87
DF6A   90 16                BCC $DF82
DF6C   A5 EE                LDA $EE
DF6E   C9 F9                CMP #$F9
DF70   F0 2B                BEQ $DF9D
DF72   88                   DEY
DF73   B9 13 FE             LDA $FE13,Y
DF76   30 25                BMI $DF9D
                            .END