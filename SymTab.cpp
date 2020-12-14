//
//		Implementation of the symbol table class.
//
#include "stdafx.h"
#include "SymTab.h"

/*
NAME

    AddSymbol - adds a new symbol to the symbol table.

SYNOPSIS

    void AddSymbol( char *a_symbol, int a_loc );

DESCRIPTION

    This function will place the symbol "a_symbol" and its location "a_loc"
    in the symbol table.
*/
void SymbolTable::AddSymbol( string &a_symbol, int a_loc )
{
    // If the symbol is already in the symbol table, record it as multiply defined.
    map<string, int>::iterator st;
    st = m_symbolTable.find( a_symbol );
    if( st != m_symbolTable.end() ) 
    {
        st->second = -999;
        return;
    }
    // Record a the  location in the symbol table.
    m_symbolTable[a_symbol] = a_loc;
}

void SymbolTable::DisplaySymbolTable()
{
	map<string, int>::iterator iter;
	int count = 0;

	for (iter = m_symbolTable.begin(); iter != m_symbolTable.end(); ++iter)
	{
		cout << "Symbol #" << setw(9) << "Symbol" << setw(11) << "Location" << endl;
		cout << setw(4) << count << setw(11) << iter->first << setw(10) << iter->second << endl;
		count++;
	}
}