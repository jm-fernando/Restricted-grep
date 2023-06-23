#include "matcher.h"
#define END -1
#define NONSPECIAL 0
#define PERIOD 1
#define PLUS 2
#define QUESTION 3
#define IGNORE 4
#include <stdio.h>


//function that returns code of symbol as established above
int nextSymbol(char *pattern, int start){
	//if pattern is completed
	if(pattern[start] == '\0'){
		return END;
	//if symbol is period
	} else if (pattern[start] == '.'){ 
		return PERIOD;
	//if symbol is plus sign
	} else if (pattern[start] == '+'){ 
		return PLUS;
	//if symbol is question mark
	} else if (pattern[start] == '?'){ 
		return QUESTION;
	//if symbol is backslash
	} else if (pattern[start] == '\\'){ 
		return IGNORE;
	}
	//if symbol is non-special
	return NONSPECIAL; 
}

//function that checks if partial_line matches pattern, starting from
//the first char of partial_line
int matches_leading(char *partial_line, char *pattern) {
	int lineIndex = 0;
	int patternIndex = 0;
	int type = nextSymbol(pattern, patternIndex);
	//while we can get another symbol from the pattern and line to be analyzed
	while(partial_line[lineIndex]!='\n' && partial_line[lineIndex]!='\0' && type != END){
		//if it's a period
		if(type == PERIOD){
			//read the next line symbol and ignore it
			lineIndex++;
			patternIndex++;
		} else if(type == PLUS){ //if it's a plus sign
			while(partial_line[lineIndex] == partial_line[lineIndex-1]){
				lineIndex++;
			}
			patternIndex++;
		} else if(type == QUESTION){ //if it's a question mark
			// we already processed the optional symbol
			patternIndex++;
		} else if(type == IGNORE){ //if symbol is for ignoring the special symbol
			patternIndex++;
			type = NONSPECIAL;
		}

		//if it's any not special symbol
		if(type == NONSPECIAL){
			// if pattern symbol must be equal to the line symbol
			if(partial_line[lineIndex] == pattern[patternIndex]){
				lineIndex++;
				patternIndex++;
			}
			// else if the next symbol is a question mark
			else if(nextSymbol(pattern, patternIndex+1) == QUESTION){
				patternIndex++;
			} else { // if they are not equal, the pattern doesn't match
				return 0;
			}
		}
		// Get the next symbol
		type = nextSymbol(pattern, patternIndex);
	}
	//if there is still a pattern but no line to be analyzed, the pattern doesn't match
	if(type != END){
		return 0;
	} 
	return 1;
}

//initializing rgrep_matches function
int rgrep_matches(char *line, char *pattern) {
	int i = 0;
	// Iterate through the line until a pattern emerges or it reaches end of line
	while(line[i] != '\n' && line[i] != '\0'){
		// If pattern is matched, return 1
		if(matches_leading(line+i, pattern)){
			return 1;
		}
		i++;
	}
	//if pattern doesn't match, return 0
    return 0;
}
