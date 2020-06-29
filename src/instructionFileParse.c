#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <instructionFileParse.h>
#include <utils.h>

modrmList_t *modrmList;
instructionIMM_t *instructionsIMM;
instructionRR_t *instructionsRR;
oneForOne_t *oneForOne;

uint64_t instructionIMMsize = 0, instructionRRsize = 0, modrmSize = 0, oneForOneSize = 0;

static void addNewInstructionIMM(char *instruction, uint8_t *encodingBytes, uint8_t size) {
    static uint64_t maxSize = 20;
    if(++instructionIMMsize == maxSize) {
        maxSize += 20;
        instructionsIMM = realloc(instructionsIMM, maxSize * sizeof(instructionIMM_t));
    }
    
    instructionIMM_t newInstruction = { instruction, encodingBytes, size };
    instructionsIMM[instructionIMMsize - 1] = newInstruction;
}

static void addNewInstructionRR(char *instruction, uint8_t *encodingBytes, uint8_t size) {
    static uint64_t maxSize = 20;
    if(++instructionRRsize == maxSize) {
        maxSize += 20;
        instructionsRR = realloc(instructionsRR, maxSize * sizeof(instructionRR_t));
    }

    instructionRR_t newInstruction = { instruction, encodingBytes, size };
    instructionsRR[instructionRRsize - 1] = newInstruction;
}

static void addNewMODRM(char *identifier, uint8_t *encoding) {
    static uint64_t maxSize = 20;
    if(++modrmSize == maxSize) {
        maxSize += 20;
        modrmList = realloc(modrmList, maxSize * sizeof(modrmList_t));
    }

    modrmList_t newInstruction = { identifier, encoding };
    modrmList[modrmSize - 1] = newInstruction;
}

static void addNewOneForOne(char *identifier, uint8_t *encodingBytes, uint8_t size) {
    static uint64_t maxSize = 20;
    if(++oneForOneSize == maxSize) {
        maxSize += 20;
        oneForOne = realloc(oneForOne, maxSize * sizeof(oneForOne_t));
    }

    oneForOne_t newInstruction = { identifier, encodingBytes, size };
    oneForOne[oneForOneSize - 1] = newInstruction;
}

static void setSection(uint8_t *holder, char *line) {
    if(strncmp(line, "ONE_FOR_ONE", strlen(line) - 1) == 0) { /* strlen(line) - 1 cuz of \n */
        holder[0] = ONE_FOR_ONE; 
    } else if(strncmp(line, "INSTRUCTIONS_IMM", strlen(line) - 1) == 0) {
        holder[0] = IMM_INSTRUCTION_ENCODING; 
    } else if(strncmp(line, "REG_ON_REG_MODRM", strlen(line) - 1) == 0) { 
        holder[0] = MODRM_ENCODING; 
    } else if(strncmp(line, "INSTRUCTIONS_REG_ON_REG", strlen(line) - 1) == 0) {
        holder[0] = RR_INSTRUCTION_ENCODING;
    }
}

static uint8_t calcuateEncodingSize(char *identifier) { 
    char encoding[50] = { 0 };
    char tmpEncoding[50] = { 0 };
    strncpy(encoding, identifier + findChar(identifier, '~') + 2, strlen(identifier) - findChar(identifier, '~') - 3);
    strcpy(tmpEncoding, encoding);

    uint8_t extraSize = 0;

    char *words;
    words = strtok(tmpEncoding, " ");
    while(words != NULL) {
        //printf("%s", words);
        if(strcmp(words, "imm8") == 0) {
            extraSize += 1;
        } else if(strcmp(words, "imm16") == 0) {
            extraSize += 2;
        } else if(strcmp(words, "imm32") == 0) {
            extraSize += 4;
        } else if(strcmp(words, "imm64") == 0) {
            extraSize += 8;
        } else if(strcmp(words, "reg_on_reg_modrm") == 0) {
            extraSize += 1;
        }
        words = strtok(NULL, " ");
    }
   
    uint8_t cnt = 0;
    for(int i = 0; i < 50; i++) {
        if(encoding[i] == ' ')
            cnt++;
    }

    //printf("%d for %s", cnt + 1 + extraSize, encoding, findChar(identifier, '~'));
    return (cnt) ? cnt + extraSize : cnt + 1;
}

static void showInstructions(void) {
    for(uint64_t i = 0; i < instructionIMMsize; i++) {
        printf("instructions IMM | %s | %s | %d\n", instructionsIMM[i].identifier, instructionsIMM[i].encoding, instructionsIMM[i].encodingSize); 
    }

    for(uint64_t i = 0; i < modrmSize; i++) {
        printf("modrm | %s | %s\n", modrmList[i].identifier, modrmList[i].encodingBytes);
    }

    for(uint64_t i = 0; i < oneForOneSize; i++) { 
        printf("one for one | %s | %s | %d\n", oneForOne[i].identifier, oneForOne[i].encoding, oneForOne[i].encodingSize);
    }

    for(uint64_t i = 0; i < instructionRRsize; i++) {
        printf("instructions RR | %s | %s | %d\n", instructionsRR[i].identifier, instructionsRR[i].encoding, instructionsRR[i].encodingSize);
    }
}

void parseInstructionFile(void) {
	FILE *fp;
    char line[100];
    char filename[] = "instructionList.txt";

    fp = fopen(filename, "r");
    if(!fp) {
        printf("Could not open file %s", filename);
        return;
    }

    instructionsIMM = malloc(20 * sizeof(instructionIMM_t));
    instructionsRR = malloc(20 * sizeof(instructionRR_t));
    oneForOne = malloc(20 * sizeof(oneForOne_t));
    modrmList = malloc(20 * sizeof(modrmList_t));

    uint8_t currentSection = 0;
    while(fgets(line, 100, fp)) {
        setSection(&currentSection, line);
       
        int64_t characterAt = findChar(line, '~');
        if(characterAt == -1) 
            continue;

        char *identifier;
        identifier = malloc(characterAt); 
        strncpy(identifier, line, characterAt - 1);

        uint8_t *encoding = malloc(50);
        memset(encoding, 0, 50);
        memcpy(encoding, line + findChar(line, '~') + 2, strlen(line) - findChar(line, '~') - 3);

        switch(currentSection) {
            case MODRM_ENCODING: 
                addNewMODRM(identifier, encoding);
                break;
            case IMM_INSTRUCTION_ENCODING: 
                addNewInstructionIMM(identifier, encoding, calcuateEncodingSize(line));
                break;
            case RR_INSTRUCTION_ENCODING: 
                addNewInstructionRR(identifier, encoding, calcuateEncodingSize(line));
                break;
            case ONE_FOR_ONE: 
                addNewOneForOne(identifier, encoding, calcuateEncodingSize(line));
                break;
        }
    }

    showInstructions();

    fclose(fp);
}

instructionIMM_t *grabIMMinstructions(void) {
	return instructionsIMM;
} 

instructionRR_t *grabRRinstructions(void) {
	return instructionsRR;
}

oneForOne_t *grabOneForOneInstructions(void) {
	return oneForOne;
}

modrmList_t *grabMODRMlist(void) {
	return modrmList;
}
