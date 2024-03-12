//Program which implements AI techniques, backward and forward chaining to diagnose and treat 30 cardiac diseases

#include <iostream>
#include <vector>
#include <string>
#include<list>
#include<map>
#include <unordered_map>
#include <stack>
#include <algorithm>
#include <string.h>
#include <queue>
#include <string>


#include <fstream>
#include <unistd.h>

#include <chrono>
using namespace std;
using namespace std::chrono;



// Defining a structure to represent a rule
struct Rule_type {
    int ruleIndex;  // Index of the rule
    vector<string> conditions;
    string conclusion;
};

// Define a structure to represent a conclusion
struct Conclusion_list {
    int ruleno;
    string varname;
};



struct stack_type {
    int ruleno;
    int clauseno;
};

struct Derived_global{
    string variable;
    string instantiated;
    string value;
};

//forward chaining structures

using namespace std;
struct forward_rule_type {
    int ruleIndex;  // Index of the rule
    vector<string> conditions;
    vector<string> treatment;
};


// Initialize the Backward chaining rule list
vector<Rule_type> rule_list = {
{10,    {"ARRHYTHMIA=YES" , "SWELLING=YES" , "WEIGHTGAIN=YES"},
"ISCHEMIC CARDIOMYOPATHY"},

{20,    {"CHESTPAIN=YES", "FATIGUE=YES" , "SHORTNESSOFBREATH=WLD" , "FEVER=NO" , "BLRYVISION=YES", "HEARTPALPITATION=YES"},
"ARRHYTHMIA"},

//change after stack test
//{10, {"CHESTPAIN=YES" , "FATIGUE=NO",  "SHORTNESSOFBREATH=YES" ,"FAINTING=YES", "NOISYGASPING=NO", "WEAKENINGINLEFTVENTRICLE=NO", "NECKTIGHTNESS=YES", "HEARTPALPITATION=YES", "CARDIACARST=YES"}, "VENTRICULAR TACHYCARDIA"},

//{20,  {"CHESTPAIN=YES" , "FATIGUE=NO" , "SHORTNESSOFBREATH=YES",  "FAINTING=YES",  "NOISYGASPING=NO", "WEAKENINGINLEFTVENTRICLE=YES",  "LOWBP=YES", "HEARTPALPITATION=YES"}, "TAKOTSUBO CARDIOMYOPATHY (BROKEN HEART SYNDROME)"},

{30,    {"CHESTPAIN=YES", "FATIGUE=NO", "SHORTNESSOFBREATH=YES" , "FAINTING=YES", "NOISYGASPING=YES", "SEIZURES=YES"},"LONG QT SYNDROME"},

{40,    {"CHESTPAIN=YES", "FATIGUE=YES", "SHORTNESSOFBREATH=ALLTIME", "FEVER=NO", "SHOULDERPAIN=NO", "BACKPAIN=NO", "DIZZINESS=YES", "IRREGULARHEARTBEAT=NO", "NAUSEA=YES"}, "PAROXYSMAL ATRIAL FIBRILLATION"},

{50,    {"CHESTPAIN=YES", "FATIGUE=YES", "SHORTNESSOFBREATH=NEVER", "SWELLING=YES", "BLUESKIN=YES", "DIZZINESS=YES",  "INCREASEDABDOMINALSIZE=YES"},
"PULMONARY HYPERTENSION"},

{60,    {"CHESTPAIN=YES", "FATIGUE=YES",  "SHORTNESSOFBREATH=ALLTIME",  "FEVER=NO",  "SHOULDERPAIN=NO",  "BACKPAIN=YES", "COUGH=YES", "SCRTHVOICE=YES"}
,"AORTIC ANEURSYM"},

{70,    {"CHESTPAIN=YES", "FATIGUE=YES", "SHORTNESSOFBREATH=ALLTIME", "FEVER=NO", "SHOULDERPAIN=NO", "BACKPAIN=NO", "DIZZINESS=YES", "IRREGULARHEARTBEAT=YES"},
"VALVULAR HEART DISEASE"},

{80,    {"CORONARY ARTERY DISEASE=YES", "NAUSEA=YES", "INDIGESTION=YES", "FAINTING=YES" ,"HEAVYSWEATING=YES"},
"ACUTE CORONARY SYNDROME"},

{90,    {"CHESTPAIN=YES", "FATIGUE=YES" , "SHORTNESSOFBREATH=ALLTIME ", "FEVER=NO" , "SHOULDERPAIN=YES" , "HEARTPALPITATION=YES" , "NECKJWPAIN=YES"},
"CORONARY ARTERY DISEASE"},

{100,   {"CHESTPAIN=YES", "FATIGUE=YES",  "SHORTNESSOFBREATH=ALLTIME", "FEVER=YES", "HEARTMURMUR=NO", "SWOLLENJOINTS=YES" , "UNCONTROLLEDMOVEMENT=YES", "SKINLUMPS=YES"},
"RHEUMATIC HEART DISEASE"},

{110,   {"PULMONARY EMBOLISM=YES" , "REDLIMB=YES", "TENDERNESSOFTHIGH=YES", "WARMSKIN=YES"},
 "VENOUS THROMBOEMBOLISM"},

{120,   {"CHESTPAIN=YES", "FATIGUE=YES", "SHORTNESSOFBREATH=ALLTIME", "FEVER=YES", "HEARTMURMUR=YES", "SKINBUMPS=NO", "BLOODINCOUGH=YES", "DISCOLOREDSKIN=YES"},
"PULMONARY EMBOLISM"},

{130,   {"CHESTPAIN=YES" , "FATIGUE=YES" , "SHORTNESSOFBREATH=ALLTIME", "FEVER=YES", "HEARTMURMUR=YES", "SKINBUMPS=YES" },
"ENDOCARDITIS"},

/*{140, {"ARRHYTHMIA=YES" , "SWELLING= YES" , "WEIGHTGAIN=YES"},
"ISCHEMIC CARDIOMYOPATHY"},

{150,   {"CHESTPAIN=YES", "FATIGUE=YES" , "SHORTNESSOFBREATH=LYINGDOWN" , "FEVER=NO" , "BLRYVISION=YES", "HEARTPALPITATION=YES"},
"ARRHYTHMIA"},*/
{140, {"CHESTPAIN=YES" , "FATIGUE=NO",  "SHORTNESSOFBREATH=YES" ,"FAINTING=YES", "NOISYGASPING=NO", "WEAKENINGINLEFTVENTRICLE=NO", "NECKTIGHTNESS=YES", "HEARTPALPITATION=YES", "CARDIACARST=YES"}, "VENTRICULAR TACHYCARDIA"},

{150,   {"CHESTPAIN=YES" , "FATIGUE=NO" , "SHORTNESSOFBREATH=YES",  "FAINTING=YES",  "NOISYGASPING=NO", "WEAKENINGINLEFTVENTRICLE=YES",  "LOWBP=YES", "HEARTPALPITATION=YES"}, "TAKOTSUBO CARDIOMYOPATHY"},

{160,   {"CHESTPAIN=YES","FATIGUE=YES", "SHORTNESSOFBREATH=LYINGDOWN", "FEVER=NO", "BLRYVISION=NO", "DIFFICULTYINWALKING=YES" , "SWELLING=YES" , "PREFERSITTING=YES"},
 "HEART VALVE STENOSIS"},

{170,   {"CHESTPAIN=YES" , "FATIGUE=YES", "SHORTNESSOFBREATH=LYINGDOWN" , "FEVER=NO" , "BLRYVISION=NO" , "DIFFICULTYINWALKING=NO", "FAINTING=YES" , "IRREGULARHEARTBEAT=YES" , "HEARTPALPITATION=YES" , "SEIZURES=YES" },
 "BRUGADA SYNDROME"},

{180,   {"PERICARDITIS=YES","INFECTIONORWOUND=YES", "CANCER=YES"},
"CARDIAC TAMPONADE"},

{190,   {"CHESTPAIN=YES" , "FATIGUE=YES" , "SHORTNESSOFBREATH=LYINGDOWN" , "FEVER=YES" , "SWEATCHILLS=YES" , "HEARTPALPITATION=YES", "DIZZINESS=YES"},
 "PERIPHERAL ARTERY DISEASE"},

{200,  {"CHESTPAIN=YES", "FATIGUE=YES", "SHORTNESSOFBREATH=ACTIVITY", "FAINTING=NO", "SLURREDSPEECH=NO","SLEEPPROBLEM=YES", "LACKOFENERGY=YES"},
"CORONARY MICROVASCULAR DISEASE"},

{210,   {"CHESTPAIN=YES", "FATIGUE=YES" , "SHORTNESSOFBREATH=ACTIVITY" , "FAINTING=NO" , "SLURREDSPEECH=NO" , "SLEEPPROBLEM=NO" , "DIZZINESS=YES" , "IRREGULARHEARTBEAT=YES" , "NAUSEA=YES" , "HEARTPALPITATION=YES" , "UPRARMPAIN=YES"},
"CHRONIC TOTAL OCCLUSION"},

{220,   {"CHESTPAIN=YES" , "FATIGUE=YES",  "SHORTNESSOFBREATH=ACTIVITY" , "FAINTING=NO" , "SLURREDSPEECH=YES" , "ONEEYEVISIONLOSS=YES" , "LEGCRMP=YES"},
"ATHEROSCLEROSIS"},

{230,   {"CHESTPAIN=YES", "FATIGUE=YES" , "SHORTNESSOFBREATH=ACTIVITY" , "FAINTING=YES" , "DIZZINESS=YES" , "HEARTMURMUR=YES" , "SWELLING=YES" , "NMBNESS=NO"},
 "HYPERTROPHIC CARDIOMYOPATHY"},

{240, {"CHESTPAIN=YES", "FATIGUE=YES", "SHORTNESSOFBREATH=ACTIVITY ", "FAINTING=YES", "DIZZINESS=YES", "HEARTMURMUR=YES", "SWELLING=YES" , "NMBNESS=YES" , "FAMILYHISTORYOFCARDIACARREST= NO" , "FAMILYHISTORYOFMITRALVALVEPROLAPSE=YES"},
"MITRAL VALVE PROLAPSE"},

{250,   {"CHESTPAIN=YES", "FATIGUE=YES" , "SHORTNESSOFBREATH=ACTIVITY", "FAINTING=YES"," DIZZINESS=YES"," HEARTMURMUR=YES", "SWELLING=YES", "NMBNESS=YES" , "FAMILYHISTORYOFCARDIACARREST=YES"},
"HYPERTROPHIC OBSTRUCTIVE CARDIO MYOPATHY"},

{260,   {"CHESTPAIN=YES", "FATIGUE=YES", "SHORTNESSOFBREATH=ACTIVITY" , "FAINTING=YES", "DIZZINESS=YES", "HEARTMURMUR=NO" , "BLOODINCOUGH=YES", "BLUECOLORSKIN=YES" , "HEARTPALPITATION=YES"},
"EISENMENGER SYNDROME"},

{270,   {"MYOCINFCTN=YES" , "LESSURIN=YES", "PALESKN=YES"},
"CARDIOGENIC SHOCK"},

{280, {"CHESTPAIN=YES",  "FATIGUE=YES", "SHORTNESSOFBREATH=SUDDEN", "SWEATCHILLS=YES",  "BDYPAIN=YES"}, "MYOCARDIAL INFARCTION"},

{290, {"CHESTPAIN=YES" , "FATIGUE=YES",  "SHORTNESSOFBREATH=DURINGEPISODESOFRAPIDHEARTRATE",  "FAINTING=YES",  "DIZZINESS=YES",  "HEARTPALPITATION=YES" , "ANXIETY=YES"} , "WOLFF-PARKINSON-WHITE SYNDROME"},

{300, {"CHESTPAIN=YES",  "FATIGUE=YES" , "SHORTNESSOFBREATH=ACTIVITY", "FAINTING=YES",  "DIZZINESS=YES" , "HEARTMURMUR=NO" , "BLOODINCOUGH=YES" , "SLEEPPROBLEM=YES" ,"SWELLING=YES"}, "AORTIC STENOSIS"}

};

//forward chaining rules
vector<forward_rule_type> fw_rule_list = {

{10, {"CORONARY ARTERY DISEASE=yes", "High cholesterol?=yes" , "Smoking?=yes" , "over weight?=yes"}, {"Stop smoking","Include healthy diet","Maintain healthy lifestyle","Exercise","Atorvastattin","Aspirin","Vasodilators"}},
{20, {"AORTIC STENOSIS=yes" , "Severe symptoms=no" , "Pulmonary congestion=yes" , "Angina?=yes"}, {"Healthy lifestyle","Mild exercise","Lisinopril","Carvedilol","Furosemide","Digoxin"}},
{30, {"ARRHYTHMIA=yes" , "Angina?=yes" , "High BP?=yes"}, {"Verapamil","propranolol","warfarin"}},
{40, {"HYPERTROPHIC CARDIOMYOPATHY=yes" , "High cholesterol?=yes"}, {"Healthy food and lifestyle","atenolol","disopramide","verapramil","warfiarin","atorvastatin"}},
{50, {"PERIPHERAL ARTERY DISEASE=yes" , "Smoking?=yes" , "physically active?=no" , "High cholesterol?=yes" , "type 2 diabetes?=yes" , "have High BP?=yes"}, {"Start with gentle physical activity","aspirin","atorvastatin","meglitinides","warfarin","cilostazol"}},
{60, {"AORTIC ANEURSYM=yes" , "High BP?=yes" , "High cholesterol?=yes" }, {"Atenolol","losartan","atorvastatin"}},
{70, {"VALVULAR HEART DISEASE=yes" , "High BP?=yes"}, {"Digidoxin","atenolol","amlodipine","diuretics","lisinopril"}},
{80, {"ENDOCARDITIS=yes" , "used antibiotics for 2-6 weeks ?=yes" , "symptoms reduced ?=no"}, {"Repair damaged heart valve","aortic valve replacement surgery","draining abscesses and repairing fistulas"}},
{90, {"PULMONARY HYPERTENSION=yes" , "are you pregnant?=no" , "sleep apnea ?=yes"}, {"Epoprostenol","riociguat","bosentan","sildenafil","amlodipine","warfarin","digoxin"}},
{100, {"WOLFF-PARKINSON-WHITE SYNDROME=yes" , "have symptoms often?=yes"}, {"Catherer ablation","cardioversion procedure","adinosine"}},
{110, {"ACUTE CORONARY SYNDROME=yes" , "High cholesterol?=yes" , "High BP?=yes" , "Arrhythmia?=yes"}, {"Aspirin","nitroglycerin","thrombolytics","metoprolol","lisinopril","irbesartin","ezetimibe","atorvastatin"}},
{120, {"LONG QT SYNDROME=yes" , "want to be athlete or be more physically active ?=no"}, {"Healthy lifestyle","nadolol","mexiletine"}},
{130, {"PAROXYSMAL ATRIAL FIBRILLATION=yes" , "Smoking?=yes" , "consume alcohol ?=yes" , "being stressful ?=yes"}, {"Stop smoking","limit alcohol consumption","start a healthy lifestyle","practice stress-relieving","digoxin","procainamide","warfarin"}},
{140, {"TAKOTSUBO CARDIOMYOPATHY=yes" }, {"Restrict tobacco use","manage stress","aspirin","diuretics","benzaprazil","atenolol"}},
{150, {"VENTRICULAR TACHYCARDIA=yes" , "High BP?=yes" , "High cholesterol?=yes" , "Smoking?=yes" , "consume alcohol ?=yes"}, {"Eat low fat, low salt diet","exercise often","stop using tobacco","norvasc","atenolol","amiodarone"}},
{160, {"BRUGADA SYNDROME=yes" , "Arrhythmia?=yes" , "high fever ?=yes"}, {"Quinidine","fever reducing medicine"}},
{170, {"ISCHEMIC CARDIOMYOPATHY=yes" , "obese ?=yes" , "family history of this disease ?=yes" , "High BP?=yes" , "High cholesterol?=yes" , "consume drugs ?=yes" , "Smoking?=yes" , "swelling in the legs ?=yes" }, {"Avoid drugs","stop smoking","eat healthy diet","atenolol","norvasac","atorvastatin","warfarin","furosemide"}},
{180, {"CHRONIC TOTAL OCCLUSION=yes"  , "Angina?=yes" , "mild chest pain ?=yes"}, {"Adopt healthy lifestyle","regular checkups","aspirin","atenolol","atorvastatin","norvasc","nitrates"}},
{190, {"CORONARY MICROVASCULAR DISEASE=yes" , "suffering from pain ?=yes" , "lifestyle changes didn't work ?=yes"}, {"Cholesterol medication","bp medication","nitroglycerin","norvasc","atenolol","antiplatelet medicine"}},
{200, {"CARDIAC TAMPONADE=yes" , "chest X-ray shows enlarged heart ?=yes" , "decrease in BP while inhaling ?=yes" , "abnormalities in 2D echo ?=yes"}, {"Required hospitalization","bed-rest with leg elevation","dobutamine","iv fluids","external oxygen supply","pericardiocentesis"}},
{210, {"PULMONARY EMBOLISM=yes" , "blood oxygen is low ?=yes" , "D-dimer blood result is high?=yes" , "consume alcohol ?=yes"}, {"Stop consuming alcohol","heparin","warfarin","regular checkups"}},
{220, {"CARDIOGENIC SHOCK=yes" , "decrease in BP while inhaling ?=yes" , "abnormalities in ECG ?=yes" , "X-ray shows fluid in lungs=yes"}, {"Emergency life support needed","iv fliuds","aspirin","vasopressers","antiplatelet medication","blood thinning medication"}},
{230, {"ATHEROSCLEROSIS=yes" , "High BP?=yes" , "physically active?=yes" , "being stressful ?=yes" , "type 2 diabetes?=yes"}, {"Healthy lifestyle","stress management","be physically active","metformin","nitrates","atenolol","norvasc","anti-clotting medicine"}},
{240, {"HEART VALVE STENOSIS=yes" , "high fever ?=yes" , "irregular heart beat ?=yes"}, {"Regular checkups with doctor","diuretics","anticoagulants","antibiotics","atenolol","norvasc"}},
{250, {"EISENMENGER SYNDROME=yes" , "blood oxygen is low ?=yes" , "chest X-ray shows enlarged heart ?=yes" , "abnormalities in the complete blood count?=yes"}, {"Antibiotics","Anticoagulants","Diuretics","Dual endothelin receptor antagonists","Iron supplements","Supplemental oxygen"}},
{260, {"MITRAL VALVE PROLAPSE=yes" , "High BP?=yes" , "chest X-ray shows enlarged heart ?=yes" , "able to do stress tests ?=yes"}, {"Atenolol","diuretics","amiodarane","anti-coagulants"}},
{270, {"RHEUMATIC HEART DISEASE=yes"}, {"Pencillin","antibiotics","aspirin","steroids"}},
{280, {"VENOUS THROMBOEMBOLISM=yes" , "Age greater than 65=yes" , "obese ?=yes" , "low oxygen levels using pulse oximetry ?=yes" }, { "apixaban","rivaroxaban"}},
{290, {"HYPERTROPHIC OBSTRUCTIVE CARDIO MYOPATHY=yes"}, {"Atenolol","dysopyramide","norvasc"}},
{300, {"MYOCARDIAL INFARCTION=yes" , "Little or no blood flow in some areas=yes" , "increased clot formation in blood=yes" }, {"Supplementary oxygen","Anti-clotting medications","Nitroglycerin","Thrombolytic (clot-busting) medications","Anti-arrhythmia medications","Pain medications"}}

};
   
//Backward chaining datastructures
vector<Conclusion_list> cncl_var_list(30);
unordered_map<string, string> varhashMap(30);
map<int,string> clausevarlist[400];
stack<stack_type> conclusionStack;
vector<string> conclusionList;
unordered_map<string,string> derivedGlobalVariableList(30);
//Forward Chaining datastructures
queue<string> con_var_q;
unordered_map<string, string> fw_varhashMap(30); // variable list
vector<string>derived_con_list{}; //derived_con_list
std::unordered_map<int,int>cls_var_pointer; //pointer
map<int,string> fw_clausevarlist[400];
queue<string>q;

void process_mem_usage(double& vm_usage, double& resident_set);
//Backward chaining functions
int Attacks_BW();
string Process(string goal);
void initializeDS();
int search_con(string variable,int index);
int rule_to_clause(int ruleno);
void update_VL(int clauseno);
void validate_Ri(int ruleNo, string& conclusion);
//Forward Chaining functions
int Prevention_FW(string disease);
void fw_Process(string value);
void fw_initializeDS();
void search_cvl(string variable);
void clause_to_rule(int clauseno);
void fw_update_VL(int clauseno);
void validate_Ri(int ruleno);

//calculating space
void process_mem_usage(double& vm_usage, double& resident_set)
{
    vm_usage     = 0.0;
    resident_set = 0.0;

    // the two fields we want
    unsigned long vsize;
    long rss;
    {
        std::string ignore;
        std::ifstream ifs("/proc/self/stat", std::ios_base::in);
        ifs >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore
                >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore
                >> ignore >> ignore >> vsize >> rss;
    }

    long page_size_kb = sysconf(_SC_PAGE_SIZE) / 1024; // in case x86-64 is configured to use 2MB pages
    vm_usage = vsize / 1024.0;
    resident_set = rss * page_size_kb;
}



void initializeDS(){
      //Intializing the conclusionList??
    for(Rule_type rule : rule_list){
        string conclusion = rule.conclusion;
        conclusionList.push_back(conclusion);
    }
     //Intializing the conclusion variable list
    for(int i=0;i<30;i++){     
       cncl_var_list[i].ruleno = 10*(i+1); 
       cncl_var_list[i].varname = "disease";

    }
   
    
    //Initializing the variable list 
    for(Rule_type rule : rule_list){
        vector<string> condList = rule.conditions; 
        for(string cond : condList){
            size_t pos = cond.find("=");
            string cond_name = cond.substr(0,pos);
            string cond_val = cond.substr(pos+1);
            //if cond_name not there in conclusion list add it to variable list
            auto it = find(conclusionList.begin(), conclusionList.end(), cond_name);
            if (it == conclusionList.end()) {    
            varhashMap[cond_name] = "NI";
            }
            else {
            std::size_t index = std::distance(conclusionList.begin(), it);
            cncl_var_list[index].varname = cond_name;    
            }
        }
    }

    int clausenum=1;
   //Initializing Clause Variable list
    for(Rule_type rule : rule_list){
         vector<string> condList = rule.conditions; 
         array<string,15> temparr;
         for(int i=0;i<15;i++){
            temparr[i]="";
         }
       int ind=0;
       for(string cond : condList){
            size_t pos = cond.find("=");
            string cond_name = cond.substr(0,pos);
            string cond_val = cond.substr(pos+1);
            temparr[ind] = cond_name;
            ind++;
        }
        for(int i=0;i<15;i++){
            clausevarlist->insert(pair<int,string>(clausenum+i,temparr[i]));
        }
        clausenum += 15;
    }

    /*cout << "print variable list" << "\n";
    for (auto i = varhashMap.begin(); i != varhashMap.end(); i++) 
          cout << i->first << " \t\t\t" << i->second << endl; 

   cout << "printing clause variable list" << "\n";
    for (auto i = clausevarlist->begin(); i != clausevarlist->end(); i++) 
          cout << i->first << " \t\t\t" << i->second << endl;
 
   cout << "printing conclusion variable list" << "\n";
   for(Conclusion_list c:cncl_var_list)  {
    cout<<"\n Rule: \n"<<c.ruleno;
    cout<<"\n conc variable: \n"<<c.varname;
   }*/
}

// finds the given variable name in conclusion list
int search_con(string variable,int index){
  /* for(int i=0; i < cncl_var_list.size(); i++){
    int res  = (cncl_var_list[index].varname).compare(variable);
       if(res == 0){
         return cncl_var_list[index].ruleno;
    //   }
        }
    return -1; */

    int res  = (cncl_var_list[index].varname).compare(variable);
    if(res==0){
       return cncl_var_list[index].ruleno; 
    }
    else{
        return -1;
    }


}

// finds the clause no for given rule no
int rule_to_clause(int ruleno){
    stack_type item;
    item.ruleno = ruleno;
    item.clauseno = 15 * ((ruleno / 10) - 1) + 1;
    
    // Push the item onto the conclusionStack
    conclusionStack.push(item);

    return item.clauseno;
    
}

void update_VL(int clauseno){
 

    string userinput;
    
    //for each variable in clausevarlist we have to find its value in varhashMap and cncl_var_list
    for(int clnum=clauseno;clnum<clauseno+15;clnum++){

        auto questionvar =  clausevarlist->find(clnum);
        string questoask = questionvar->second; // //for example cp in clause variable list 
    if(!(questoask == "")){

        bool inconclusionvarList=false;
        for(int i=0;i<30;i++){     
        if(cncl_var_list[i].varname == questoask){
            inconclusionvarList=true;
            break;
        }}
      
        if(inconclusionvarList){

            Process(questoask);
            
        }
        else{
            auto it = varhashMap.find(questoask);
            string val = it->second;
            int res = val.compare("NI");
            if(res == 0){
                
                 cout << "\nDo you have " << questoask << " ? " << "\n";
                  if(questoask=="SHORTNESSOFBREATH")   {
                    cout << "\nPlease enter your symptom from anyone below:\nWLD : If you have symptom while lying down\n"; 
                    cout << "\nNEVER: If you never have this symptom \n";
                    cout << "\nYES : If you are unsure when you are short of breath \n";
                    cout << "\nALLTIME : If you are experiencing shortness of breath all the time \n";
                    cout << "\nLYINGDOWN : If you experience shortness of breath while lying down occasionally \n";
                    cout << "\nACTIVITY : If you experience shortness of breath during physical activity \n";
                    cout << "\nSUDDEN : If you experience shortness of breath suddenly \n";
                    cout << "\nDURINGEPISODESOFRAPIDHEARTRATE : If you experience shortness of breath whenever heart rate increases\n";
                 }
                 else{
                    cout<< "\nEnter YES or NO as answer \n";
                 }
                 cin >> userinput;
                 varhashMap[questoask] = userinput;
         
            }
       }
    }
    else{
            break;
        }
    }
   
}

void validate_Ri(int ruleNo, string& conclusion) {
    bool conditionSatisfied;
    bool allconditionsSatisfied=true;
    Rule_type checkedRule;

    for (const Rule_type& rule : rule_list) {
        if (rule.ruleIndex == ruleNo) {
            checkedRule=rule;
            break;}
    }
    

    for(string cond : checkedRule.conditions){
        conditionSatisfied=true;  
        size_t pos = cond.find("=");
        string cond_name = cond.substr(0,pos);
        string cond_val = cond.substr(pos+1);

        if (varhashMap[cond_name].compare(cond_val)!=0 && derivedGlobalVariableList[cond_name].compare(cond_val)!=0) {//check case lower,upper
            conditionSatisfied = false;
            break;
            }
            
        } 
    if(!conditionSatisfied){
        allconditionsSatisfied=false;
        }

    if(allconditionsSatisfied){
       
        conclusion=checkedRule.conclusion;
        derivedGlobalVariableList[conclusion]="YES";
        stack_type top;
        top=conclusionStack.top();
        if(top.ruleno==checkedRule.ruleIndex){ 
            conclusionStack.pop();
            }
        //cout<< "all conditions satisfied: " <<conclusion;
    } 
    //cout<<"after setting derived global"<<derivedGlobalVariableList[conclusion];
     
}
     

string Process(string goal) {
    //loop through each conclusion variable to find value for goal which is disease initially
    int i=0;
    string conclusion="";

    while(i<cncl_var_list.size()){

        int rulenum = search_con(goal,i);
    
        if(rulenum==-1){
            i=i+1;
            continue;
        }  

        int clauseno = rule_to_clause(rulenum);
      

        update_VL(clauseno);

        /*cout << "print variable list" << "\n";
        for (auto i = varhashMap.begin(); i != varhashMap.end(); i++) 
            cout << i->first << " \t\t\t" << i->second << endl;*/

        conclusion="";
        validate_Ri(rulenum,conclusion);

        if (!conclusion.empty()) {
                    // A conclusion was found, you can save it or use it as needed
                    break;  // End the program after updating the Variable List
                }
        else{
            i=i+1;
        }        
    }  
return conclusion;
}  

int Attacks_BW(){
    vector<int> values(10000);
    auto start = high_resolution_clock::now();
    
    initializeDS();
    cout<< "Welcome to Intelligent Cardiac Diagnosis System \n";
    cout<< "Please answer the following questions so we can diagnose your disease \n";
    string conclusion = Process("disease");
    cout<< "You have been diagnosed with: \n"<<conclusion;
    

 // Call the function, here sort()
 sort(values.begin(), values.end());

 // Get ending timepoint
 auto stop = high_resolution_clock::now();

 // Get duration. Substart timepoints to 
 // get duration. To cast it to proper unit
 // use duration cast method
    auto duration = duration_cast<microseconds>(stop - start);
    cout<<"\n Time taken by Backward chaining:\n"<<duration.count() <<"microsec";

    start = high_resolution_clock::now();

    Prevention_FW(conclusion);
    // Call the function, here sort()
    sort(values.begin(), values.end());

    // Get ending timepoint
    stop = high_resolution_clock::now();

 // Get duration. Substart timepoints to 
 // get duration. To cast it to proper unit
 // use duration cast method
    duration = duration_cast<microseconds>(stop - start);
    cout<<"\n Time taken by Forward chaining:\n"<<duration.count() <<"microsec";
    return 0;
}

//forward chaining
void fw_initializeDS(){
   
    //Initializing the variable list
    for(forward_rule_type rule : fw_rule_list){
        vector<string> condList = rule.conditions; 
        for(string cond : condList){
            size_t pos = cond.find("=");
            string cond_name = cond.substr(0,pos);
            string cond_val = cond.substr(pos+1);

		fw_varhashMap[cond_name] = "NI"; 
        }
    }

    int clausenum=1;
   //Initializing Clause Variable list
    for(forward_rule_type rule : fw_rule_list){
         vector<string> condList = rule.conditions; 
         array<string,10> temparr;
         for(int i=0;i<10;i++){
            temparr[i]="";
         }
       int ind=0;
       for(string cond : condList){
            size_t pos = cond.find("=");
            string cond_name = cond.substr(0,pos);
            string cond_val = cond.substr(pos+1);
            temparr[ind] = cond_name;
            ind++;
        }
        for(int i=0;i<10;i++){
            fw_clausevarlist->insert(pair<int,string>(clausenum+i,temparr[i]));
        }
        clausenum += 10;
    }

    /*cout << "print variable list" << "\n" ;
    for (auto i = fw_varhashMap.begin(); i != fw_varhashMap.end(); i++) 
          cout << i->first << " \t\t\t" << i->second << endl;

   cout << "printing clause variable list" << "\n";
    for (auto i = fw_clausevarlist->begin(); i != fw_clausevarlist->end(); i++) 
          cout << i->first << " \t\t\t" << i->second << endl;
*/
}

void search_cvl(string variable){
	//cout << "search_cvl variable name " << " " << variable << endl;//ruleno=-1 case??
	for(int i= 0;i<400;i++)
	{
		for(auto it=fw_clausevarlist[i].begin(); it!=fw_clausevarlist[i].end(); ++it)
		{
			if(it->second == variable)
			{	
				int clauseno = it->first;
				//cout << "clauseno" << " " <<clauseno << endl;
				fw_update_VL(clauseno);
				clause_to_rule(clauseno);
				break;
			}
		}
	}
   
}

void fw_update_VL(int clauseno)
{
	string userinput;
	for(int clnum=clauseno;clnum<clauseno+10;clnum++)
	{

		auto questionvar =  fw_clausevarlist->find(clnum);
		
        	string questoask = questionvar->second; // DIS HICOL

    		if(!(questoask == "")){
       
      
        		//cout<< "qn from clause varlist:"<<questoask << "\n";//handle questoask==""here
        		auto it = fw_varhashMap.find(questoask);
       		 	string val = it->second;
        		int res = val.compare("NI");//result if variable Instantiated in variable list or not
        		if(res ==0)
			{
				cout<<questoask <<""<<endl;
				cin>>userinput;
				fw_varhashMap[questoask] = userinput;
            			
            			//cout << "value intialized in variable list";

			}

		}
		else
		{
			break;
		}
	}

 
}

void clause_to_rule(int clauseno){
  
	int ruleno= ((clauseno/10)+1)*10;
	//cout << "rule no " << " " << ruleno << endl;//ruleno=-1 case??
	validate_Ri(ruleno);

    
}

void validate_Ri(int ruleno)
{

    bool conditionSatisfied;
    bool allconditionsSatisfied=true;
    forward_rule_type checkedRule;

    for (const forward_rule_type& rule : fw_rule_list) {
        if (rule.ruleIndex == ruleno) {
            checkedRule=rule;
            break;
	}
    }
    //cout<< "Rule's validity checking : "<<checkedRule.ruleIndex;

    for(string cond : checkedRule.conditions){
        conditionSatisfied=true;  
        size_t pos = cond.find("=");
        string cond_name = cond.substr(0,pos);
        string cond_val = cond.substr(pos+1);
       
	//cout<<"cond_val "<<cond_val<<endl;
	std::string VLvalue = fw_varhashMap[cond_name];
	//cout<<"VLvalue "<<VLvalue<<endl;
	std::transform(VLvalue.begin(), VLvalue.end(), VLvalue.begin(), ::toupper);
	//cout<<"UPPER VLvalue "<<VLvalue<<endl;
	std::string cond_val_uppr = cond_val;
	//cout<<"cond_val "<<cond_val<<endl;
	std::transform(cond_val_uppr.begin(), cond_val_uppr.end(), cond_val_uppr.begin(), ::toupper);
	//cout<<"UPPER cond_val_uppr "<<cond_val_uppr<<endl;


        if (VLvalue!=cond_val_uppr) {//check case lower,upper
            conditionSatisfied = false;
            //cout<< "breaks at : "<< cond_name;
            break;
            }
        } 
    if(!conditionSatisfied){
        allconditionsSatisfied=false;
	cout<<"Exercise regularly"<<endl;
        }
    //cout<< "all conditions satisfied: " <<allconditionsSatisfied;

    if(allconditionsSatisfied){
       string con_var="Treatment";
       // cout<< "all conditions satisfied: " <<endl;
 	vector<string> trtmntList=checkedRule.treatment;
	cout<< "\n Treatment we recommend is: \n " <<endl;
	for(string trtmnt : trtmntList)
	{
		
		cout<<trtmnt <<endl;
		derived_con_list.push_back(trtmnt);

	}
	q.push(con_var);
	
    }   


}

void fw_Process(string value) {
	for (auto i = fw_varhashMap.begin(); i != fw_varhashMap.end(); i++)
	{
		//cout <<"variable and value -----"<< value <<" " << i->first<< endl;

		if(value == i->first)
		{
			fw_varhashMap[value] = "YES";
			//cout <<"value of var list after update"<< fw_varhashMap[value] << endl;
			
		}
		
		//cout<<"After update :"<<endl;
         	//cout << i->first << " \t\t\t" << i->second << endl; 
		
	} 

	search_cvl(value);
}  

int Prevention_FW(string dis){

    fw_initializeDS();
	//string variable = "DIS";
	//string dis =	"Acute Coronary Syndrome"; // get value from BW
    cout<<"\n";
    cout<<"\nPlease answer few more questions below to get proper treatment: \n";
    fw_Process(dis);// val of dis
    return 0;
}

int main(){
    Attacks_BW();
   double vm, rss;
   process_mem_usage(vm, rss);
   cout << "VM: " << vm << "; RSS: " << rss << endl;
    return 0;
}
