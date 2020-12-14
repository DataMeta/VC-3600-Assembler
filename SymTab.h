//
//		Symbol table class.
//
#pragma once



// This class is our symbol table.
class SymbolTable {

public:
    SymbolTable( ) {};
    ~SymbolTable( ) {};

    void AddSymbol( string &a_symbol, int a_loc );
	void DisplaySymbolTable();
    bool LookupSymbol( string &a_symbol, int &a_loc );

	map<string, int> GetSymbolTable()
	{
		return m_symbolTable;
	}

private:
    // This is the actual symbol table.  The symbol is the key to the map.
    map<string, int> m_symbolTable;
};