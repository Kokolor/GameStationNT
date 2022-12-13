ENTRY(start)
SECTIONS
{
	. = 0x00100000;
	.text ALIGN(0x1000) :
	{
		*(.multiboot)
		*(.text)
	}
	.text BLOCK(4K) : ALIGN(4K)
	{
		*(.text)
	}
	.rodata BLOCK(4K) : ALIGN(4K)
	{
		*(.rodata)
	}
	.data BLOCK(4K) : ALIGN(4K)
	{
		*(.data)
	}
}