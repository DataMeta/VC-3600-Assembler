//
//      Implementation of the Assembler class.
//
#include "stdafx.h"
#include "Assembler.h"
#include "SymTab.h"
#include "Errors.h"

// Constructor for the assembler.
Assembler::Assembler( int argc, char *argv[] )
: m_facc( argc, argv )
{
    // Nothing else to do here.
}
// Destructor currently does nothing.
Assembler::~Assembler( )
{
}
// Pass I establishes the location of the labels.
void Assembler::PassI( ) 
{
    int loc = 0;        // Tracks the location of the instructions to be generated.

    // Successively process each line of source code.
    for( ; ; ) 
    {
        // Read the next line from the source file.
        string buff; 
        if( ! m_facc.GetNextLine( buff ) )
        {
            // If there are no more lines, we are missing an end statement.
            // We will let this error be reported by Pass II.
            return;
        }
        // Parse the line and get the instruction type.
        Instruction::InstructionType st =  m_inst.RecordInstruction( buff );      

        // If this is an end statement, there is nothing left to do in pass I.
        // Pass II will determine if the end is the last statement.
        if( st == Instruction::ST_End ) return;

        // Labels can only be on machine language and assembler language instructions.
        if( st != Instruction::ST_MachineLanguage && st != Instruction::ST_AssemblerInstr ) continue;

        // If the instruction has a label, record it and its location in the symbol table.
        if( m_inst.isLabel( ) ) 
        {
            m_symtab.AddSymbol( m_inst.GetLabel( ), loc );
        }
        // Compute the location of the next instruction.
        loc = m_inst.LocationNextInstruction( loc );
    }

}

void Assembler::PassII()
{
	int loc = 0;        // Tracks the location of the instructions to be generated.
	m_facc.rewind();

	// Successively process each line of source code.
	for (;;) 
    {
		// Read the next line from the source file.
		string buff;
		if (!m_facc.GetNextLine(buff)) 
        {
			// If there are no more lines, we are missing an end statement.
			// We will let this error be reported by Pass II.
			return;
		}
		// Parse the line and get the instruction type.
		Instruction::InstructionType st = m_inst.RecordInstruction(buff);

		// Pass II will determine if the end is the last statement.
		if (st == Instruction::ST_End) return;

		// Labels can only be on machine language and assembler language instructions.
		if (st != Instruction::ST_MachineLanguage && st != Instruction::ST_AssemblerInstr) continue;

		m_inst.PrintHeading(loc);

		m_inst.Translate(loc, buff, m_symtab.GetSymbolTable());

		loc = m_inst.LocationNextInstruction(loc);
	}
}

void Assembler::RunEmulator()
{

}
