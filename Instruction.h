//
// Class to manage instructions
//
#pragma once
#include "Assembler.h"
#include "SymTab.h"
#include "stdafx.h"
// The elements of an instruction.
class Instruction 
{

public:

    Instruction( ) { };
    ~Instruction( ) { };

    // Codes to indicate the type of instruction we are processing.
    enum InstructionType 
	{
        ST_MachineLanguage, 
        ST_AssemblerInstr,  
        ST_Comment,         
        ST_End              
    };

    // Record and parse the Instruction.
	InstructionType RecordInstruction(string &a_buff)
	{     
		istringstream input2(a_buff);
		m_line = a_buff;

		unsigned int a_pos = m_line.find(";");
		m_Comment = "";

		// Stores comment
		for (a_pos; a_pos < a_buff.length(); a_pos++)
		{
			m_parsechar = a_buff[a_pos];
			m_Comment += m_parsechar;
		}

		// cout << m_Comment << endl;

		// Removes comment
		if (a_buff.length() != 0)
		{
			m_line = m_line.substr(0, m_line.find(";")); 
		}
		
		istringstream input(m_line);
		int count = 0;

		// Count how many parts were on the line
		string a_currentPart = "";
		for (;;) 
		{
			a_currentPart = "";
			input >> a_currentPart;

			if (a_currentPart.size() == 0) 
			{
				break;
			}
			count++;
		}

		// Reset the istreamstream so we can use it again
		input = istringstream(m_line);
		m_parser1 = ""; m_parser2 = ""; m_parser3 = "";

		if (count == 0 && m_Comment != "")
		{
			m_Label = m_parser1;
			m_OpCode = m_parser2;
			m_Operand = m_parser3;
			m_type = ST_Comment;
		}
		if (count == 3)
		{
			input >> m_parser1 >> m_parser2 >> m_parser3;
			m_Label = m_parser1;
			m_OpCode = m_parser2;
			m_Operand = m_parser3;
			//cout << m_Label << " " << m_OpCode << " " << m_Operand;
		}
		else if (count == 2) 
		{
			input >> m_parser2 >> m_parser3;
			m_Label = m_parser1;
			m_OpCode = m_parser2;
			m_Operand = m_parser3;
			//cout << m_OpCode << " " << m_Operand;
		}
		else if (count == 1)
		{
			input >> m_parser2;
			m_Label = m_parser1;
			m_OpCode = m_parser2;
			m_Operand = m_parser3;
			//cout << m_OpCode;
		}
		else if (count == 0)
		{
			m_Label = m_parser1;
			m_OpCode = m_parser2;
			m_Operand = m_parser3;
			//cout << m_OpCode;
		}
		
		if (m_OpCode == "add" || m_OpCode == "sub" || m_OpCode == "mult" || m_OpCode == "div" ||
			m_OpCode == "load" || m_OpCode == "store" || m_OpCode == "read" || m_OpCode == "write" ||
			m_OpCode == "b" || m_OpCode == "bm" || m_OpCode == "bz" || m_OpCode == "bp" || m_OpCode == "halt")
		{
				m_type = ST_MachineLanguage;
		}
		else if (m_OpCode == "dc" || m_OpCode == "ds" || m_OpCode == "org")
		{
				m_type = ST_AssemblerInstr;
		}
		else if (m_OpCode == "end")
		{
			m_type = ST_End;
		}
		else if (m_OpCode == "")
		{
			m_type = ST_Comment;
		}
		return m_type;
	};

    // Compute the location of the next instruction.    
	int LocationNextInstruction(int a_loc){

		// If the line is empty, do nothing
		if (m_OpCode == "")
		{
			//cout << " " << a_loc << endl;
			return a_loc;
		}

		// If org is called, then set a_loc to the value of the following operand
		else if (m_OpCode == "org")
		{
			m_OperandValue = atoi(m_Operand.c_str());
			a_loc = m_OperandValue;
			//cout << " " << a_loc << endl;
			return a_loc;
		}

		// If ds is called, then increment a_loc with the following operand
		else if (m_OpCode == "ds")
		{
			m_OperandValue = atoi(m_Operand.c_str());
			a_loc += m_OperandValue;
			//cout << " " << a_loc << endl;
			return a_loc;
		}

		// All other cases increment a_loc by 1
		else 
		{
			a_loc++;
			//cout << " " << a_loc << endl;
			return a_loc;
		}
	};

    // To access the label								
    inline string &GetLabel( ) 
	{
        return m_Label;
	};

    // To determine if a label is blank.
	inline bool isLabel() 
	{
		return !m_Label.empty();
	};

	void PrintHeading(int a_loc)
	{
		if (a_loc == 0)
		{
			cout << endl << endl << "Translation Of Program:" << endl << endl;
			cout << "Location" << setw(10) << "Contents" << setw(20) << "Original Statement" << setw(0) << endl
				<< endl;
		}
	};

	void Translate(int a_loc2, string a_buff2, map<string, int> a_RefMap)		// UNDER CONSTRUCTION [...] 
	{												
		if (m_OpCode == "add") m_ValOpCode = "01";	
		if (m_OpCode == "sub") m_ValOpCode = "02";
		if (m_OpCode == "mult") m_ValOpCode = "03";
		if (m_OpCode == "div") m_ValOpCode = "04";
		if (m_OpCode == "load") m_ValOpCode = "05";
		if (m_OpCode == "store") m_ValOpCode = "06";
		if (m_OpCode == "read") m_ValOpCode = "07";
		if (m_OpCode == "write") m_ValOpCode = "08";
		if (m_OpCode == "b") m_ValOpCode = "09";
		if (m_OpCode == "bm") m_ValOpCode = "10";
		if (m_OpCode == "bz") m_ValOpCode = "11";
		if (m_OpCode == "bp") m_ValOpCode = "12";
		if (m_OpCode == "halt") m_ValOpCode = "13";

		if (m_OpCode == "add" || m_OpCode == "sub" || m_OpCode == "mult" || m_OpCode == "div" ||
	        m_OpCode == "load" || m_OpCode == "store" || m_OpCode == "read" || m_OpCode == "write" ||
			m_OpCode == "b" || m_OpCode == "bm" || m_OpCode == "bz" || m_OpCode == "bp")
		{
			_itoa_s(a_RefMap[m_Operand], convArray, 10);
			m_LocOperand = convArray;
			m_Contents = m_ValOpCode + m_LocOperand;
		}

		else if (m_OpCode == "dc")
		{	
			m_ValOpCode = "00";
			m_LocOperand = m_Operand;
			m_Contents = m_ValOpCode + m_LocOperand;
		}

		else if (m_OpCode == "end" || m_OpCode == "end" || m_OpCode == "ds")
		{
			m_Contents == "";
		}
		
		else if (m_OpCode == "halt")
		{
			m_LocOperand = "0000";
			m_Contents = m_ValOpCode + m_LocOperand;
		}

		/*else if (m_type == ST_Comment && m_Label == "" && m_OpCode == "" && m_Operand == "")
		{
			cout << m_Comment << endl;
		}*/

		cout << a_loc2 << setw(15) << m_Contents
		<< setw(7) << m_Label << setw(7) << m_OpCode << setw(5) << m_Operand << m_Comment << endl;
		
			//cout << m_Label << setw(7) << m_OpCode << setw(5) << m_Operand << m_Comment << endl;
	};

private:

    // The elements of a instruction
    string m_Label;			 // The label.
    string m_OpCode;		 // The symbolic op code.
    string m_Operand;		 // The operand.

	string m_Comment;
	char m_parsechar;		 
	char convArray[50];

    string m_instruction;    // The original instruction.
	string m_line;			 // Contains a_buff for parsing
	string m_temp;			 // Contains a_buff for separate substring operation
	string m_parser1;		 // Temporary container for the label part of the line
	string m_parser2;		 // Temporary container for the opcode part of the line
	string m_parser3;		 // Temporary container for the operand part of the line

    // Derived values.
    int m_NumOpCode;		 // The numerical value of the op code.
	string m_ValOpCode;
	string m_LocOperand;
	string m_Contents;

    InstructionType m_type;  // The type of instruction.

    bool m_IsNumericOperand; // == true if the operand is numeric.
    int m_OperandValue;		 // The value of the operand if it is numeric.
};