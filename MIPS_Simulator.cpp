#include <iostream>
#include <istream>
#include <fstream>
#include <vector>
#include <string>


using namespace std;

struct Memory_line {
    int address;
    int data;
};

struct IFbuffer{
    string instruction;
    string instr;
    string rs;
    string rt;
    string rd;
    string imm;
};
struct IDbuffer{
    string instruction;
    int rs;
    int rt;
    string imm;
    int regDestination;
    bool validBit;
};
struct EXEbuffer{
    string instruction;
    int ALUdata;
    int writeToMemData;
    int regDestination;
    bool validBit;
};
struct MEM_Accessbuffer{
    string instruction;
    int dataFromAlu;
    int dataFromMem;
    int regDestination;
    bool AorM;//get data from Alu or memory
    bool validBit;//if branch is taken there gonna be flush if valitbit=false then i print "-"
};

struct WBbuffer {
    int regDestination;
    int data;
};

///MONITORS
int n1,n2,n8,n9,n10,n11,n16,n17,n18,n19,n20,n21,n23,n26;
string s4,s5,s6,s7,s12,s13,s14,s15,s24,s25;
int registers[31];
///emine to 22 na do pou enna mpi..


/*
IFbuffer iFetchBuffer;
IDbuffer iDecodeBuffer;
EXEbuffer executionBuffer;
MEM_Accessbuffer memAccessbuffer;
WBbuffer WBackbuffer;*/



int add(int rs, int rt){
    int sum;
    sum = rs +rt;
    return sum;
}
int sub(int rs, int rt)
{
    int sum;
    sum = rs - rt;
    return sum;
}
int subu(int rs, int rt)
{
    int sum;
    sum = rs - rt;
    return sum;
}
int AND(int rs, int rt)
{
    int sum;
    sum = rs & rt;
    return sum;
}
int OR(int rs, int rt)
{
    float sum;
    sum = rs | rt;
    return sum;
}
int ori(int rs, int immediate){
    int sum = 0;
    sum  = rs | immediate;
    return sum;
}
int addi(int rs, int immediate)
{
    int sum;
    sum = rs + immediate;
    return sum;
}
int addiu(int rs, int immediate){

    int sum;
    sum = rs + immediate;
    return sum;
}
int addu(int rs, int rt){
    int sum;
    sum = rs + rt;
    return sum;
}
int andi(int rs, int immediate)
{
    int sum;
    sum = rs && immediate;
    return sum;
}
bool beq(int rs, int rt)
{
    return rs == rt;
}
bool bne(int rs, int rt){
    return rs != rt;
}
int lw(int rs, int offset){//addres apo tin mnimi
    int sum;
    sum = rs + offset;
    return sum;
}
int sw(int rs, int offset){//addresss stin mnimi
    int sum;
    sum = rs + offset;
    return sum;
}
int NOR(int rs, int rt)
{
    int sum;
    int result;
    sum = rs | rt;
    result = !sum;
    return result;
}
int sll(int rt, int sh_amm){
    return rt << sh_amm;
}
int srl(int rt, int sh_amm){
    return rt >> sh_amm;
}
int slt(int rs, int rt) {
    if (rs < rt){
        return 1;
    }
    else
        return 0;
}
int sltu(int rs, int rt) {
    if (rs < rt){
        return 1;
    }
    else
        return 0;
}
int slti(int rs, int immediate) {
    if (rs < immediate){
        return 1;
    }
    else
        return 0;
}
int sltiu(int rs, int immediate) {
    if (rs < immediate){
        return 1;
    }
    else
        return 0;
}
int branch_to(string str, vector<string>labels){
    for (int i = 0; i < labels.size(); ++i) {
        if (labels[i] == str)
            return i;
    }
}

int opcode(string str) {
    if (str == "add" || str == "and" || str == "addu" || str == "nor" || str== "or" || str == "slt" || str == "sltu" || str == "sub" || str == "subu")
        return 0;
    else if(str == "addi" || str == "addiu" || str == "andi" || str == "ori" || str == "slti" || str == "sltiu" )
        return 1;
    else if(str == "sll" || str == "srl")
        return 2;
    else if(str == "sw")
        return 3;
    else if(str == "lw")
        return 4;
    else if(str == "bne" || str == "beq")
        return 5;
    else if(str[0] == 'j')
        return 6;
    else
        return -1;
}
int map_reg(string str){
    if (str == "v0")
        return 0;
    else if (str == "v1")
        return 1;
    else if (str == "a0")
        return 2;
    else if (str == "a1")
        return 3;
    else if (str == "a2")
        return 4;
    else if (str == "a3")
        return 5;
    else if (str == "t0")
        return 6;
    else if (str == "t1")
        return 7;
    else if (str == "t2")
        return 8;
    else if (str == "t3")
        return 9;
    else if (str == "t4")
        return 10;
    else if (str == "t5")
        return 11;
    else if (str == "t6")
        return 12;
    else if (str == "t7")
        return 13;
    else if (str == "s0")
        return 14;
    else if (str == "s1")
        return 15;
    else if (str == "s2")
        return 16;
    else if (str == "s3")
        return 17;
    else if (str == "s4")
        return 18;
    else if (str == "s5")
        return 19;
    else if (str == "s6")
        return 20;
    else if (str == "s7")
        return 21;
    else if (str == "t8")
        return 22;
    else if (str == "t9")
        return 23;
    else if (str == "k0")
        return 24;
    else if (str == "k1")
        return 25;
    else if (str == "gp")
        return 26;
    else if (str == "sp")
        return 27;
    else if (str == "fp")
        return 28;
    else if (str == "ra")
        return 29;
    else if (str == "zero")
        return 30;
    else if (str == "r0")
        return 31;
    else if (str == "at")
        return 32;
    else
        return (-1);
}
void printOutputFiletype(int tipoma){
    if(tipoma==0){
        ///tipose ta stixia mou
    }else if(tipoma==1){
        ///tipose ta stixeia gia ton zitoumeno kiklo
    }else if(tipoma==2){
        ///TIPOSE TO TELIKO FILE
    }
    cout<<"tipothike sto outputfile :)"<<endl;
   /* fstream outputF1;
    outputF1.open("outputfile.txt", ios::in|ios::out|ios::app);
    outputF1 << "Name: Kyprianos Andreou\nID: 968298\n\n-----Cycle";
             outputF1 << "\n\n-----Cycle " << dec << cycle << "-----\nRegister:\n" << hex << pc*4 << "\t" << registers[map_reg("r0")] << "\t";*/
}
bool comparator(int rs, int rt){
    return bne(rs,rt) || beq(rs, rt);
}

IFbuffer iFetch(string instruction,string instr, string rs, string rt, string rd, string imm,IFbuffer iFetchBuffer){
    iFetchBuffer.instruction = instruction;
    iFetchBuffer.instr = instr;
    iFetchBuffer.rs = rs;
    iFetchBuffer.rt = rt;
    iFetchBuffer.rd = rd;
    iFetchBuffer.imm = imm;
    return iFetchBuffer;

}
IDbuffer iDecode(IFbuffer ifetch, IDbuffer iDecodeBuffer) {
    int index1, index2;

    index1 = map_reg(ifetch.rs);
    index2 = map_reg(ifetch.rt);

    iDecodeBuffer.instruction = ifetch.instr;
    iDecodeBuffer.rs = index1;
    iDecodeBuffer.rt = index2;
    iDecodeBuffer.imm = ifetch.imm;
    iDecodeBuffer.regDestination = map_reg(ifetch.rd);

    if ((iDecodeBuffer.instruction == "bne" || iDecodeBuffer.instruction == "beq") && comparator(index1, index2)){//an isxoun afta kane flush diladi adiase to pipeline
        cout << "to programma vrike oti to branch tha ekstelesti" << endl;
        iDecodeBuffer.validBit = false;
    } else
        iDecodeBuffer.validBit = true;

    return iDecodeBuffer;
}
EXEbuffer iExecute(IDbuffer idecode, EXEbuffer executionBuffer) {
    int Aluout = 0, immNum = 0;
    string s;

    executionBuffer.instruction = idecode.instruction;
    executionBuffer.regDestination = idecode.regDestination;
    executionBuffer.writeToMemData = 0;
    executionBuffer.validBit = true;

    if(idecode.validBit) {
        if (idecode.instruction == "add")
            Aluout = add(registers[idecode.rs], registers[idecode.rt]);
        else if (idecode.instruction == "addu")
            Aluout = addu(registers[idecode.rs], registers[idecode.rt]);
        else if (idecode.instruction == "and")
            Aluout = AND(registers[idecode.rs], registers[idecode.rt]);
        else if (idecode.instruction == "or")
            Aluout = OR(registers[idecode.rs], registers[idecode.rt]);
        else if (idecode.instruction == "nor")
            Aluout = NOR(registers[idecode.rs], registers[idecode.rt]);
        else if (idecode.instruction == "slt")
            Aluout = slt(registers[idecode.rs], registers[idecode.rt]);
        else if (idecode.instruction == "sltu")
            Aluout = sltu(registers[idecode.rs], registers[idecode.rt]);
        else if (idecode.instruction == "sub")
            Aluout = sub(registers[idecode.rs], registers[idecode.rt]);
        else if (idecode.instruction == "subu")
            Aluout = subu(registers[idecode.rs], registers[idecode.rt]);
        else if (idecode.instruction == "addi") {
            executionBuffer.regDestination = idecode.rt;
            s = idecode.imm;
            immNum = stoi(s, nullptr, 0); //o integer arithmos gia to offset
            Aluout = addi(registers[idecode.rs], immNum);
        } else if (idecode.instruction == "addiu") {
            executionBuffer.regDestination = idecode.rt;
            s = idecode.imm;
            immNum = stoi(s, nullptr, 0); //o integer arithmos gia to offset
            Aluout = addiu(registers[idecode.rs], immNum);
        } else if (idecode.instruction == "andi") {
            executionBuffer.regDestination = idecode.rt;
            s = idecode.imm;
            immNum = stoi(s, nullptr, 0); //o integer arithmos gia to offset
            Aluout = andi(registers[idecode.rs], immNum);
        } else if (idecode.instruction == "ori") {
            executionBuffer.regDestination = idecode.rt;
            s = idecode.imm;
            immNum = stoi(s, nullptr, 0); //o integer arithmos gia to offset
            Aluout = ori(registers[idecode.rs], immNum);
        } else if (idecode.instruction == "slti") {
            executionBuffer.regDestination = idecode.rt;
            s = idecode.imm;
            immNum = stoi(s, nullptr, 0); //o integer arithmos gia to offset
            Aluout = addiu(registers[idecode.rs], immNum);
        } else if (idecode.instruction == "sltiu") {
            executionBuffer.regDestination = idecode.rt;
            s = idecode.imm;
            immNum = stoi(s, nullptr, 0); //o integer arithmos gia to offset
            Aluout = sltiu(registers[idecode.rs], immNum);
        } else if (idecode.instruction == "sll") {
            s = idecode.imm;
            immNum = stoi(s, nullptr, 0); //o integer arithmos gia to offset
            Aluout = sll(registers[idecode.rt], immNum);
        } else if (idecode.instruction == "srl") {
            s = idecode.imm;
            immNum = stoi(s, nullptr, 0); //o integer arithmos gia to offset
            Aluout = srl(registers[idecode.rt], immNum);
        } else if (idecode.instruction == "lw") {
            executionBuffer.regDestination = idecode.rt;
            s = idecode.imm;
            immNum = stoi(s, nullptr, 0); //o integer arithmos gia to offset
            Aluout = lw(registers[idecode.rs], immNum);
            executionBuffer.validBit = true;
        } else if (idecode.instruction == "sw") {
            s = idecode.imm;
            immNum = stoi(s, nullptr, 0);//o integer arithmos gia to offset
            Aluout = sw(registers[idecode.rs], immNum);
            executionBuffer.writeToMemData = idecode.rt;
        } else if (idecode.instruction == "-")
            cout << "label" << endl;
        else
            cout << "this instruction have not been created yet: " << idecode.instruction << endl;
        executionBuffer.ALUdata = Aluout;
    }else
        executionBuffer.validBit = false;

    return executionBuffer;
}
void Pipeline(string * str, int size, int size_of_mem, vector<string> instr, vector<string>rd, vector<string>rs, vector<string>rt, vector<string>imm, vector<string> labels) {
    int i, j, k, cycles, stage, size_of_vectors, store_times = 0;
    vector<IFbuffer> IF;
    vector<IDbuffer> ID;
    vector<EXEbuffer> EXE;
    vector<MEM_Accessbuffer> MEM;
    vector<WBbuffer> WB;
    Memory_line dataMemory[size_of_mem];

    bool flag;

    registers[map_reg("gp")] = 0x10008000;
    registers[map_reg("sp")] = 0x7ffffffc;
    registers[map_reg("zero")] = 0;
    registers[map_reg("r0")] = 0;
    registers[map_reg("at")] = 0;

    IFbuffer instrFetchBuf, iftemp;
    IDbuffer instrDecodeBuf, idtemp;
    EXEbuffer instrExecuteBuf, exetemp;
    size_of_vectors = size - 1;

    instrFetchBuf.rs = "-";
    instrFetchBuf.imm = "-";
    instrFetchBuf.rt = "-";
    instrFetchBuf.instruction = "-";
    instrFetchBuf.instr = "-";
    instrFetchBuf.rd = "-";

    i = 0;
    while (i < size_of_vectors) {
        iftemp = iFetch(str[i], instr[i], rs[i], rt[i], rd[i], imm[i], instrFetchBuf);
        IF.push_back(iftemp);
        i++;
    }

    ///instruction decode
    //initialization
    instrDecodeBuf.regDestination = 0;
    instrDecodeBuf.instruction = "-";
    instrDecodeBuf.rt = 0;
    instrDecodeBuf.imm = "-";
    instrDecodeBuf.rs = 0;
    instrDecodeBuf.validBit = false;
    //kano push mia keni grammi sto vector ID
    ID.push_back(instrDecodeBuf);
    i = 1;
    while (i < size_of_vectors + 1) {
        //decode tin entoli kai kano push sto vector ID
        idtemp = iDecode(IF[i - 1], instrDecodeBuf);
        ID.push_back(idtemp);
        i++;
    }
///tipomata gia debuging
    i = 0;
    while (i < size_of_vectors) {
        cout << i << ":\ninstruction:" << IF[i].instruction << "\t\t\t" << ID[i + 1].instruction << endl;
        cout << "rs:" << IF[i].rs << "\t\t\t" << ID[i + 1].rs << endl;
        cout << "rt:" << IF[i].rt << "\t\t\t" << ID[i + 1].rt << endl;
        cout << "rd:" << IF[i].rd << "\t\t\t" << ID[i + 1].regDestination << endl;
        cout << "imm:" << IF[i].imm << "\t\t\t" << ID[i + 1].imm << "\n\n\n" << endl;
        i++;
    }
///telos tipomaton gia debuging

        instrExecuteBuf.instruction = "-";
        instrExecuteBuf.ALUdata = 0;
        instrExecuteBuf.writeToMemData = 0;
        instrExecuteBuf.regDestination = '-';
        instrExecuteBuf.validBit = false;

        //kano push 2 executebuffers
        EXE.push_back(instrExecuteBuf);
        EXE.push_back(instrExecuteBuf);
        i = 2;
    cycles=0;
        while (i < size_of_vectors + 2) {
            exetemp = iExecute(ID[i - 1], instrExecuteBuf);
            if(exetemp.validBit) {
                if (exetemp.instruction == "lw" || exetemp.instruction == "sw") {
                    if (exetemp.instruction == "lw") {
                        for (j = 0; j < size_of_mem; j++) {
                            if (dataMemory[j].address == exetemp.ALUdata) {
                                registers[exetemp.regDestination] = dataMemory[j].data;
                                break;
                            } else
                                cout << "\n" << "data not found in memory load failed" << endl;
                        }
                    } else if (exetemp.instruction == "sw") {
                        flag = false;
                        for (j = 0; j < size_of_mem; j++) {
                            if (dataMemory[j].address == exetemp.ALUdata) {
                                flag = true;
                                break;
                            }
                        }
                        if (flag) {
                            dataMemory[j].data = registers[exetemp.writeToMemData];
                        } else {
                            dataMemory[store_times].address = exetemp.ALUdata;
                            dataMemory[store_times].data = registers[exetemp.writeToMemData];
                            store_times++;
                        }
                    }
                } else
                    registers[exetemp.regDestination] = exetemp.ALUdata;
            }else{
                if(exetemp.instruction == "bne")
                   i = branch_to(ID[i-1].imm, labels);//thesi tou label sto vector

                else if(exetemp.instruction == "beq")
                   i = branch_to(ID[i-1].imm, labels);//thesi tou label sto vector
            }
            cycles++;
            i++;
        }
        ///checking memory
        i = 0;
        while (i < store_times) {
            cout << dataMemory[i].address << "\t" << dataMemory[i].data << endl;
            i++;
        }
        ///
    }
int tipos(string str) {

    int type = -1;
    int i = 0;
    int m = 0;
    int l = 0;
    int c = 0;


    while (str[i]) {

        if (str[i] == '$') {
            m++;
            i++;
        } else if (str[i] == ',') {
            l++;
            i++;
        }
        else if(str[i] == ':'){
            c++;
            i++;
        }
        else
            i++;
    }

    if ((m == 3) && (l == 2)) {
        type = 0;//R-type
    } else if ((m == 2) && (l == 2)) {
        type = 2;//shift branch addi andi ori
    } else if ((m == 2) && (l == 1)) {
        type = 1;//lw sw
    } else if ((m == 0) && (l == 0) && (c == 0)) {
        type = 3;//jump
    }
    else if(c == 1){
        type = 4;
    }
    else type = -2;

    return type;
}
void spasimo_entolis(string *str1, int *Instruction_type, int size) {
    int i = 0, j = 0, c = 0, d_size = 0,k;
    string str;
    int flag;

    vector<char> instr;
    vector<char> reg_s;
    vector<char> reg_t;
    vector<char> reg_d;
    vector<char> im;
    vector<char> label;

    vector<string> instruction;
    vector<string> register_s;
    vector<string> register_t;
    vector<string> register_d;
    vector<string> immediate;
    vector<string> Labels;


    for(i=0; i<size; i++){
        str = str1[i];
        if(Instruction_type[i] == 0){//r-type
            j=0;
            while(str[j]){
                if(str[j] == '$'){
                    j++;
                    break;
                }
                else {
                    instr.push_back(str[j]);
                    j++;
                }

            }
            string string1(instr.begin(), instr.end());
            instr.clear();
            instruction.push_back(string1);

            while(str[j]){
                if(str[j] == ','){
                    j=j+2;
                    break;
                }
                else{
                    reg_d.push_back(str[j]);
                    j++;
                }
            }

            string string2(reg_d.begin(), reg_d.end());
            reg_d.clear();
            register_d.push_back(string2);

            while (str[j]){
                if(str[j] == ','){
                    j=j+2;
                    break;
                }
                else{
                    reg_s.push_back(str[j]);
                    j++;
                }
            }

            string string3(reg_s.begin(), reg_s.end());
            reg_s.clear();
            register_s.push_back(string3);

            while(str[j]){
                if(str[j] == '\n')
                    break;
                else{
                    reg_t.push_back(str[j]);
                    j++;
                }
            }

            string string4(reg_t.begin(), reg_t.end());
            reg_t.clear();
            register_t.push_back(string4);

            immediate.push_back("-");
            Labels.push_back("-");
        }
        else if(Instruction_type[i] == 1) {//lw/sw
            j = 0;
            while (str[j]) {
                if (str[j] == '$') {
                    j++;
                    break;
                } else {
                    instr.push_back(str[j]);
                    j++;
                }
            }
            string string5(instr.begin(), instr.end());
            instr.clear();
            instruction.push_back(string5);

            while (str[j]) {
                if (str[j] == ',') {
                    j++;
                    break;
                } else {
                    reg_t.push_back(str[j]);
                    j++;
                }
            }
            string string60(reg_t.begin(), reg_t.end());
            register_t.push_back(string60);
            reg_t.clear();

            while (str[j]) {
                if (str[j] == '$') {
                    j++;
                    break;
                } else {
                    im.push_back(str[j]);
                    j++;
                }
            }
            string string52(im.begin(), im.end());
            im.clear();
            immediate.push_back(string52);

            while (str[j]) {
                if (str[j] == '\n') {
                    break;
                } else {
                    reg_s.push_back(str[j]);
                    j++;
                }
            }

            string string53(reg_s.begin(), reg_s.end());
            reg_s.clear();
            register_s.push_back(string53);

            register_d.push_back("-");
            Labels.push_back("-");
        }
        else if(Instruction_type[i] == 2){//I-type
            j=0;
            flag = 0;
            while(str[j]){
                if(str[j] == '$'){
                    j++;
                    break;
                }
                else {
                    instr.push_back(str[j]);
                    j++;
                }


            }
            string string6(instr.begin(), instr.end());
            instr.clear();
            instruction.push_back(string6);

            if ((string6 == "sll") || (string6 == "srl")){
                flag = 1;
            }
            else if((string6 == "bne") || (string6 == "beq")) {
                flag = 2;
            }
            else
                flag = 0;

            if(flag == 1){//sll/srl
                while(str[j]){
                    if(str[j] == ','){
                        j=j+2;
                        break;
                    }
                    else{
                        reg_d.push_back(str[j]);
                        j++;
                    }
                }

                string string75(reg_d.begin(), reg_d.end());
                reg_d.clear();
                register_d.push_back(string75);

                while (str[j]){
                    if(str[j] == ','){
                        j++;
                        break;
                    }
                    else{
                        reg_t.push_back(str[j]);
                        j++;
                    }
                }

                string string85(reg_t.begin(), reg_t.end());
                reg_t.clear();
                register_t.push_back(string85);

                register_s.push_back("-");
                Labels.push_back("-");

            }
            else if(flag == 0) {//addi/addiu/andi/ori/alti/sltiu//beq/bne
                while (str[j]) {
                    if (str[j] == ',') {
                        j = j + 2;
                        break;
                    } else {
                        reg_t.push_back(str[j]);
                        j++;
                    }
                }

                string string7(reg_t.begin(), reg_t.end());
                reg_t.clear();
                register_t.push_back(string7);

                while (str[j]) {
                    if (str[j] == ',') {
                        j++;
                        break;
                    } else {
                        reg_s.push_back(str[j]);
                        j++;
                    }
                }

                string string8(reg_s.begin(), reg_s.end());
                reg_s.clear();
                register_s.push_back(string8);

                register_d.push_back("-");
                Labels.push_back("-");

            }
            else if(flag == 2){//bne/beq
                while (str[j]) {
                    if (str[j] == ',') {
                        j = j + 2;
                        break;
                    } else {
                        reg_s.push_back(str[j]);
                        j++;
                    }
                }

                string string95(reg_s.begin(), reg_s.end());
                reg_s.clear();
                register_s.push_back(string95);

                while (str[j]) {
                    if (str[j] == ',') {
                        j++;
                        break;
                    } else {
                        reg_t.push_back(str[j]);
                        j++;
                    }
                }

                string string96(reg_t.begin(), reg_t.end());
                reg_t.clear();
                register_t.push_back(string96);

                register_d.push_back("-");
                Labels.push_back("-");

            }

            while (str[j]) {
                if (str[j] == '\n') {
                    break;
                } else {
                    im.push_back(str[j]);
                    j++;
                }
            }
            string string9(im.begin(), im.end());
            im.clear();
            immediate.push_back(string9);
        }
        else if(Instruction_type[i] == 3){//jump
            j=0;

            while (str[j]) {
                if (str[j] == '\n') {
                    break;
                } else {
                    instr.push_back(str[j]);
                    j++;
                }
            }

            string string10(instr.begin(), instr.end());
            instr.clear();
            instruction.push_back(string10);

            immediate.push_back("-");
            Labels.push_back("-");
            register_t.push_back("-");
            register_s.push_back("-");
            register_d.push_back("-");
        }
        else if(Instruction_type[i] == 4){//Labels
            j=0;
            while (str[j]) {
                if (str[j] == ':') {
                    break;
                } else {
                    label.push_back(str[j]);
                    j++;
                }
            }
            string string11(label.begin(), label.end());
            label.clear();
            Labels.push_back(string11);

            immediate.push_back("-");
            instruction.push_back("-");
            register_t.push_back("-");
            register_s.push_back("-");
            register_d.push_back("-");
        }
        else if(Instruction_type[i] == -2){//error
            cout << "ERROR" << endl;
        }

    }

    instruction.push_back("\0");

    while (instruction[c] != "\0"){
        if (instruction[c] == "sw")
            d_size++;
        c++;
    }
    Pipeline(str1, size, d_size, instruction, register_d, register_s, register_t, immediate, Labels);

}

void instruction_mem1(int size) {
    int i = 0, j = 0, c = 0, p = 0;
    string str1[size];
    int typos_entolis[size];

    ifstream file("temp1.txt");
    if (file.is_open()) {

        for (i = 0; i < size; ++i) {
            file >> str1[i];
            p++;
        }
    }
    for (j = 0; j < size; ++j) {
        c = tipos(str1[j]);
        typos_entolis[j] = c;
    }

    spasimo_entolis(str1, typos_entolis,p);
}
char *remove_parenthesis1(char *str) {
    char ch = 40;
    int i = 0, j = 0;
    while (str[i]) {
        if (str[i] != ch)
            str[j++] = str[i];
        i++;
    }
    str[j] = '\0';
    return str;
}
char *remove_parenthesis2(char *str) {
    char ch = 41;
    int i = 0, j = 0;
    while (str[i]) {
        if (str[i] != ch)
            str[j++] = str[i];
        i++;
    }
    str[j] = '\0';
    return str;
}
char *remove_enters(char *str) {
    int i = 0;
    int j = 0;
    int c = 0;
    char ch = '\n';
    while (str[i]) {
        if (str[i] == str[i + 1]) {
            if (str[i] == ch) {
                j = i;
                while (str[j]) {
                    str[j] = str[j + 1];
                    j++;
                }
                i--;
            }
        }
        i++;
    }
    return str;
}
char *removeTabs(char *str) {
    char ch = 9;
    int i = 0, j = 0;
    while (str[i]) {
        if (str[i] != ch)
            str[j++] = str[i];
        i++;
    }
    str[j] = '\0';
    return str;
}
char *r(char *str) {
    char ch = '\r';
    int i = 0, j = 0;
    while (str[i]) {
        if (str[i] != ch)
            str[j++] = str[i];
        i++;
    }
    str[j] = '\0';
    return str;
}
char *removeSpaces(char *str) {
    char ch = 32;
    int i = 0, j = 0;
    while (str[i]) {
        if (str[i] != ch)
            str[j++] = str[i];
        i++;
    }
    str[j] = '\0';
    return str;
}
int storeInstructions(int size) {
    char *array = new char[size];
    char ch;
    string sxolia;
    int c = 0;

    int i = 0, j = 0;
    ifstream myfile("simple.txt");

    if (myfile.is_open()) {
        while (!myfile.eof()) {
            if (ch == ':')
                break;
            else
                myfile.get(ch);
        }
        while (!myfile.eof()) {
            if (ch == '#') {
                c--;
                getline(myfile, sxolia);
                array[c] = '\n';
                c++;
            }
            myfile.get(ch);
            array[c] = ch;
            c++;

        }
        myfile.close();
    } else {
        cout << "ERROR opening file" << endl;
    }
    removeSpaces(array);
    removeTabs(array);
    remove_enters(array);
    remove_parenthesis1(array);
    remove_parenthesis2(array);
    r(array);

    ofstream firs_temp;
    firs_temp.open("temp1.txt");
    while (array[i] != '\0') {
        firs_temp << array[i];
        i++;
        if (array[i] == '\n')
            j++;
    }
    firs_temp.close();
    return j;
}
int size_of_file_char() {
    string sxolia;
    char ch;
    int i = 0;

    ifstream myfile("simple.txt");

    if (myfile.is_open()) {
        while (!myfile.eof()) {
            myfile.get(ch);
            i++;
        }
        myfile.close();
    } else {
        cout << "ERROR opening file" << endl;
    }
    return i;
}
int main() {
    int size_by_char = 0;
    int size_of_instr = 0;
    size_by_char = size_of_file_char();
    size_of_instr = storeInstructions(size_by_char);
    instruction_mem1(size_of_instr);
    return 0;
}
