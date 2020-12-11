/*
 *  pci.h
 *
 *  Copyright by QNX Software Systems Limited 1994. All rights reserved.
 */
#ifndef __PCI_H_INCLUDED

#ifndef __TYPES_H_INCLUDED
 #include <i86.h>
#endif

#pragma pack(1);
#ifdef __cplusplus
extern "C" {
#endif
struct _pci_regs {
        unsigned long eax, ebx, ecx, edx, esi, edi, es;
        } ;

typedef struct _pci_route_buffer {
        short unsigned  BufferSize;
        short unsigned  DataBufferOffset;
        short unsigned  DataBufferSeg;
        } IRQRoutingOptionsBuffer;

struct _pci_config_regs
{
        unsigned short          Vendor_ID;
        unsigned short          Device_ID;
        unsigned short          Command;
        unsigned short          Status;
        char                    Revision_ID;
        char                    Class_Code[3];
        char                    Cache_Line_Size;
        char                    Latency_Timer;
        char                    Header_Type;
        char                    BIST;
        unsigned long           Base_Address_Regs[6];
        unsigned long           Reserved1[2];
        unsigned long           ROM_Base_Address;
        unsigned long           Reserved2[2];
        char                    Interrupt_Line;
        char                    Interrupt_Pin;
        char                    Min_Gnt;
        char                    Max_Lat;
        char                    Device_Dependent_Regs[192];
};

#define PCI_IS_IO(address)              ((address) & 1)
#define PCI_IS_MEM(address)             (!PCI_IS_IO(address))
#define PCI_IO_ADDR(address)            ((address) & ~0x3)
#define PCI_MEM_ADDR(address)           ((address) & ~0xf)
#define PCI_ROM_ADDR(address)           ((address) >> 0xb)
#define PCI_IS_MMAP20(address)          ((address) & 0x2)
#define PCI_IS_MMAP32(address)          (!((address) & 0x6))
#define PCI_IS_MMAP64(address)          ((address) & 0x4)

#define PCI_FUNCTION_ID                 0xb1
#define PCI_BIOS_PRESENT                0x01
#define PCI_FIND_DEVICE                 0x02
#define PCI_FIND_CLASS                  0x03
#define PCI_GENERATE_SPECIAL_CYCLE      0x06
#define PCI_READ_CONFIG_BYTE            0x08
#define PCI_READ_CONFIG_WORD            0x09
#define PCI_READ_CONFIG_DWORD           0x0a
#define PCI_WRITE_CONFIG_BYTE           0x0b
#define PCI_WRITE_CONFIG_WORD           0x0c
#define PCI_WRITE_CONFIG_DWORD          0x0d
#define PCI_GET_IRQ_ROUTING_OPTIONS     0x0e
#define PCI_SET_IRQ                     0x0f

#define PCI_SUCCESS                     0x00
#define PCI_UNSUPPORTED_FUNCT           0x81
#define PCI_BAD_VENDOR_ID               0x83
#define PCI_DEVICE_NOT_FOUND            0x86
#define PCI_BAD_REGISTER_NUMBER         0x87
#define PCI_SET_FAILED                  0x88
#define PCI_BUFFER_TOO_SMALL            0x89

extern int _CA_PCI_Find_Device(unsigned devid, unsigned venid, unsigned index,
                                                                unsigned *busnum, unsigned *devfuncnum);
extern int _CA_PCI_Read_Config_Byte(unsigned busnum, unsigned devfuncnum,
                                                                unsigned offset, unsigned cnt, char *bufptr);
extern int _CA_PCI_Read_Config_Word(unsigned busnum, unsigned devfuncnum,
                                                                unsigned offset, unsigned cnt, char *bufptr);
extern int _CA_PCI_Read_Config_DWord(unsigned busnum, unsigned devfuncnum,
                                                                unsigned offset, unsigned cnt, char *bufptr);

extern int _CA_PCI_Write_Config_Byte(unsigned busnum, unsigned devfuncnum,
                                                                unsigned offset, unsigned cnt, char *bufptr);
extern int _CA_PCI_Write_Config_Word(unsigned busnum, unsigned devfuncnum,
                                                                unsigned offset, unsigned cnt, char *bufptr);
extern int _CA_PCI_Write_Config_DWord(unsigned busnum, unsigned devfuncnum,
                                                                unsigned offset, unsigned cnt, char *bufptr);
extern int _CA_PCI_Generate_Special_Cycle(unsigned Busnum,
                                                                unsigned long SpecialCycleData);
extern int _CA_PCI_Set_Hardware_Interrupt(unsigned Busnum, unsigned devfuncnum,
                                                                unsigned IntPin, unsigned IRQNum);
extern int _CA_PCI_Get_Routing_Options(struct _pci_route_buffer *rbufptr,
                                                                unsigned *IRQForPCI);
extern int _CA_PCI_Find_Class(unsigned long ClassCode, unsigned index,
                                                                unsigned *busnum, unsigned *devfuncnum);
extern int _CA_PCI_BIOS_Present(unsigned *lastbus, unsigned *version,
                                                                unsigned *hardware);


#ifdef __386__

extern int _PCI_INT(unsigned func, struct _pci_regs *regset);
#pragma aux _PCI_INT = \
        "push es" \
        "mov ecx,8[ebx]" \
        "mov edx,12[ebx]" \
        "mov esi,16[ebx]" \
        "mov edi,20[ebx]" \
        "mov  es,24[ebx]" \
        "push ebx" \
        "mov ebx,4[ebx]" \
        "push ds" \
        "push 0d0h" \
        "pop ds" \
        "mov ah,0b1h" \
        "int 1ah" \
        "pop ds" \
        "xchg eax,0[esp]" \
        "mov 4[eax],ebx" \
        "pop ebx" \
        "mov 0[eax],ebx"\
        "mov 8[eax],ecx" \
        "mov 12[eax],edx" \
        "mov 16[eax],esi" \
        "mov 20[eax],edi" \
        "mov al,bh" \
        "and eax,0ffh" \
        "pop es" \
        __parm [al] [ebx] \
        __modify __exact [eax ebx ecx edx esi edi] \
        __value [eax];

#else

extern int _PCI_INT(unsigned func, struct _pci_regs *regset);
#pragma aux _PCI_INT = \
        ".386" \
        "mov ecx,8[bx]" \
        "mov edx,12[bx]" \
        "mov esi,16[bx]" \
        "mov edi,20[bx]" \
        "mov  es,24[bx]" \
        "push bx" \
        "mov ebx,4[bx]" \
        "push ds" \
        "push 0d0h" \
        "pop ds" \
        "mov ah,0b1h" \
        "int 1ah" \
        "pop ds" \
        "xchg bx,0[esp]" \
        "mov 0[bx],eax" \
        "mov eax,ebx" \
        "pop ax" \
        "mov 4[bx],eax" \
        "mov 8[bx],ecx" \
        "mov 12[bx],edx" \
        "mov 16[bx],esi" \
        "mov 20[bx],edi" \
        "mov al,1[bx]" \
        "mov ah,0" \
        __parm [al] [bx] \
        __modify __exact [ax bx cx dx si di es] \
        __value [ax];

#endif
#ifdef __cplusplus
}
#endif
#pragma pack();

#define __PCI_H_INCLUDED
#endif
