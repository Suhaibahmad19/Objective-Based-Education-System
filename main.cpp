#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <stdint.h>
#include <string>
#include <vector>

using namespace std;

template <typename T1>
T1* FindObject(const vector<T1*>& objects, const string id)
{
    for (const auto& obj : objects)
    {
        if (obj->GetID() == id)
        {
            return obj;
        }
    }
    return nullptr;
}
template <typename T2>
void ListAllObjects(const vector<T2*>& entities)
{
    for (const auto& entity : entities)
    {
        entity->Display();
    }
}
template <typename T3>
bool RemoveObjects(vector<T3*>& entities, T3* id)
{
    auto it = find(entities.begin(), entities.end(), id);

    if (it != entities.end())
    {
        delete* it;
        entities.erase(it);
        return true;
    }
    else
        return false;
}
template <typename T4>
void Deallocation(vector<T4*>& entities)
{
    for (auto& element : entities)
    {
        delete element;
    }
    entities.clear();
}
template <typename T5>
bool CheckExistence(vector<T5*>& entities, T5* obj)
{
    for (auto& element : entities)
    {
        if (element == obj)
            return true;
    }
    return false;
}

class CLO;
class Teaching;
class Topic;
class Question;

class Entity
{
    string ID;
    string TextInfo;

public:
    void ReadDataFromUser(string id);
    void ReadDataFromFile(ifstream& filereader);
    void ReadDataFromFile(string _id, ifstream& filereader);
    void Display();
    void UpdateEnity();
    void WriteDataToFile(ofstream& writer);
    string GetID();

};

class PLO : public Entity
{
    vector<CLO*> SatisfiedBy;
    Entity* BelongsTo;

public:

    ~PLO();
    void AddCLO(CLO* ptr);
    void RemoveCLO(CLO* ptr);
    void ListCLOs();
    void SetProgramPTR(Entity* ptr);
    string GetProgramPTR();
};
class CLO : public Entity
{
    PLO* ParentPLO;
    Entity* BelongsTo; // course
    vector<Question*> TestedBy;

public:

    ~CLO();
    void SetParentPLO(PLO* ptr);
    void AddQuestion(Question* ptr);
    void RemoveQuestion(Question* ptr);
    bool IsTested();
    void SetCoursePTR(Entity* ptr);
    string GetParentID();
    void WriteCLOtoFile(ofstream& writer);

};
class Program;
class Course : public Entity
{
    vector<CLO*> CLOs;
    vector<Teaching*> AllTeachersAssigned;
    vector<Program*> IsOfferedBy;


public:

    ~Course();
    void AddCLO(CLO* ptr);
    void AddTeaching(Teaching* ptr);
    void AddPrograms(Program* ptr);
    void WriteProgramsToFile(ofstream& writer);
    vector<CLO*> GetCLOs();
    bool CheckCLOTested();
    void WriteCLOsToFile(ofstream& writer);
};
class Program : public Entity
{
    vector<PLO*> PLOs;
    vector<Course*> OfferedCourses;

public:

    ~Program();
    void AddPLO(PLO* ptr);
    void AddCourse(Course* ptr);
    void ListOfferedCourses();
};

class Teacher;
class Topic;
class Evaluation;

class Employee : public Entity
{
public:


    virtual void EmployeeMenu() {}
    virtual vector<Topic*> GetTopics();
    virtual vector<Evaluation*> GetEvals();
    virtual vector<Question*> GetQuestions();
};
class Teacher;
class Topic
{
    string Content;
    Course* CoursePTR;
    Teacher* Createdby;

public:

    Topic(string& content, Course* cptr, Teacher* tptr);
    void Display();
    void UpdateContent();
    void BackupTopicToFile(ofstream& writer);
};
class Teaching
{
    Employee* TeacherPTR;
    Course* CoursePTR;

public:

    void SetTeacher(Employee* ptr);
    void SetCourse(Course* ptr);
    Course* GetCourse();
    vector<CLO*> GetCLOs();
};
class Question
{
    CLO* coveredCLO;
    Teacher* AskedBy;
    Evaluation* EvalID;
    string Content;

public:
    void SetContent();
    void SetContent(ifstream& filereader);
    void SetCLO(CLO* ptr);
    void SetTeacher(Teacher* ptr);
    void UpdateContent();
    void SetEvalID(Evaluation* ptr);
    void BackupQuestion(ofstream& writer);
    ~Question();
};
class Teacher;
class Evaluation
    : public Entity
{ // Evaluation means quiz,assignment, mids,finals
    vector<CLO*> CoveredCLOs;
    vector<Question*> Questions;
    Teacher* Assignedby;

public:
    void AddCLO(CLO* ptr);
    void AddQuestionFromUser();
    void ReadQuestionsFromFile(ifstream& fileReader);
    void UpdateQuestion();
    void RemoveQuestion();
    void BackupEvaluationToFile(ofstream& writer);
    void SetTeacherPTR(Teacher* ptr);
    void RemoveQuestion(Question* ptr) {
        RemoveObjects(Questions, ptr);
    }
    vector<Question*> GetAllQuestions();

    ~Evaluation();
};

class AcademicOfficer : public Employee
{
public:


    void AddProgramFromUser();
    void AddPLOFromUser();
    void AddCourseFromUser();
    void AddCLOFromUser();
    void EmployeeMenu();
    void AddEntities();
    void UpdateEntities();
    void RemoveEntities();
};
class Teacher : public Employee
{
    vector<Teaching*> AllCoursesAssigned;
    vector<Topic*> TopicsCovered;
    vector<Evaluation*> Evaluations;

public:


    void AddTeaching(Teaching* ptr);
    vector<CLO*> GetCLOsOfCourses();
    Course* FindAssignedCourse(string id);

    void AddTopicFromFile(ifstream& fileReader);
    void ReadEvalsFromFile(ifstream& fileReader);
    void ReadQuestionsFromFile(ifstream& fileReader);

    void AddTopicFromUser();
    void AddEvalsFromUser();
    void AddQuestionFromUser();

    void UpdateTopic();
    void UpdateEvaluation();
    void UpdateQuestion();

    void RemoveTopic();
    void RemoveEvaluation();
    void RemoveQuestion();

    void AddItem();
    void UpdateItem();
    void RemoveItem();

    vector<Topic*> GetTopics();
    vector<Evaluation*> GetEvals();
    vector<Question*> GetQuestions();

    void EmployeeMenu();
};

class OBE
{
    vector<Program*> AllPrograms;
    vector<Course*> AllCourses;
    vector<PLO*> AllPLOs;
    vector<CLO*> AllCLOs;
    vector<Employee*> AllEmployees;
    vector<Teaching*> CourseRegistration;

    Employee* CurrEmployee;
    static OBE* OBEExist;

    OBE() {}

public:
    ~OBE() {
        system("cls");
        SystemBackup();
        cout << "================================================================" << endl;
        cout << "|                                                              |" << endl;
        cout << "|          ~Hope You Are Satisfied With our OBE System~        |" << endl;
        cout << "|                                                              |" << endl;
        cout << "================================================================" << endl;
    }
    static OBE* CreateOBE();
    Employee* getCurrEmployee();

    void AddProgram(Program* ptr);
    void AddCourse(Course* ptr);
    void AddPLO(PLO* ptr);
    void AddCLO(CLO* ptr);
    void AddEmployee(Employee* ptr);

    void SignUp();
    void LogIn();
    void SystemBackup();
    void SystemSetup();
    void ViewReports();

    Program* FindProgram(string id);
    Course* FindCourse(string id);
    PLO* FindPLO(string id);
    CLO* FindCLO(string id);
    Employee* FindEmployee(string id);

    void ListAllPrograms();
    void ListAllCourses();
    void ListAllEmployees();
    void ListAllPLOs();
    void ListAllCLOs();

    void ReadProgramsFromFile(string fileName);
    void ReadCoursesFromFile(string fileName);
    void ReadEmployeesFromFile(string filename);
    void ReadPLOsFromFile(string filename);
    void ReadCLOsFromFile(string filename);
    void ReadTeachingsFromFile(string filename);
    void ReadTopicsFromFile(string filename);
    void ReadEvaluationsFromFile(string filename);
    void ReadQuestionsFromFile(string filename);

    bool RemoveProgram(string id);
    bool RemoveCourse(string id);
    bool RemovePLO(string id);
    bool RemoveCLO(string id);

    void CLOReport();
    void CLOsOfCourseReport();
    void CLOsOfPLO();

    void BackupEmployees(string filename);
    void BackupPrograms(string filename);
    void BackupCourses(string filename);
    void BackupPLOs(string filename);
    void BackupCLOs(string filename);
    void BackupTopics(string filename);
    void BackupEvals(string filename);
    void BackupQuestions(string filename);

    vector<Topic*> GetAllTopics();
    vector<Evaluation*> GetAllEvals();
    vector<Question*> GetAllQs();

    void MainMenu();
};

int main()
{
    OBE* OBEsystem = OBE::CreateOBE();
    OBEsystem->SystemSetup();

    OBEsystem->MainMenu();

    Employee* curr = OBEsystem->getCurrEmployee();
    if (curr != nullptr)
        curr->EmployeeMenu();

    delete OBEsystem;
}

void Entity::ReadDataFromUser(string id)
{

    ID = id;
    cout << "Enter Text: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, TextInfo);
}
void Entity::ReadDataFromFile(ifstream& filereader)
{
    filereader >> ID;
    filereader.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(filereader, TextInfo);
}
void Entity::ReadDataFromFile(string _id, ifstream& filereader)
{

    ID = _id;
    filereader.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(filereader, TextInfo);
}
void Entity::WriteDataToFile(ofstream& writer)
{
    writer << ID << "\n";
    writer << TextInfo << "\n";
}
void Entity::UpdateEnity()
{
    cout << "Enter New text: " << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, TextInfo);
}
void Entity::Display() { cout << ID << " - " << TextInfo << endl; }
string Entity::GetID() { return ID; }

void PLO::AddCLO(CLO* ptr) { SatisfiedBy.push_back(ptr); }
void PLO::RemoveCLO(CLO* ptr) { RemoveObjects(SatisfiedBy, ptr); }
void PLO::ListCLOs()
{
    if (SatisfiedBy.size() > 0)
        ListAllObjects(SatisfiedBy);
    else
        cout << "No CLOs created under this PLO" << endl;
}
void PLO::SetProgramPTR(Entity* ptr) { BelongsTo = ptr; }
string PLO::GetProgramPTR() { return BelongsTo->GetID(); }

void CLO::SetParentPLO(PLO* ptr) { ParentPLO = ptr; }
void CLO::AddQuestion(Question* ptr) { TestedBy.push_back(ptr); }
void CLO::RemoveQuestion(Question* ptr) { RemoveObjects(TestedBy, ptr); }
bool CLO::IsTested()
{
    if (TestedBy.size() >= 2)
    {
        return true;
    }
    else
    {
        return false;
    }
}
void CLO::SetCoursePTR(Entity* ptr) { BelongsTo = ptr; }
void CLO::WriteCLOtoFile(ofstream& writer)
{
    WriteDataToFile(writer);
    writer << ParentPLO->GetID() << "\n";
    writer << BelongsTo->GetID() << "\n";
}
string CLO::GetParentID() { return ParentPLO->GetID(); }

bool Course::CheckCLOTested()
{

    for (int i = 0; i < CLOs.size(); i++)
    {
        if (CLOs[i]->IsTested() == false)
            return false;
    }
    return true;
}
void Course::AddCLO(CLO* ptr) { CLOs.push_back(ptr); }
void Course::AddTeaching(Teaching* ptr) { AllTeachersAssigned.push_back(ptr); }
void Course::WriteCLOsToFile(ofstream& writer)
{
    for (int i = 0; i < CLOs.size(); i++)
    {
        writer << CLOs[i]->GetID() << " ";
    }
    writer << "-1\n";
}
vector<CLO*> Course::GetCLOs() { return CLOs; }
void Course::AddPrograms(Program* ptr) {
    IsOfferedBy.push_back(ptr);
}
void Course::WriteProgramsToFile(ofstream& writer) {
    for (int i = 0; i < IsOfferedBy.size(); i++)
    {
        writer << IsOfferedBy[i]->GetID() << " ";
    }
    writer << -1 << "\n";
}

void Program::AddPLO(PLO* ptr) { PLOs.push_back(ptr); }
void Program::AddCourse(Course* ptr) { OfferedCourses.push_back(ptr); }
void Program::ListOfferedCourses() { ListAllObjects(OfferedCourses); }


Topic::Topic(string& content, Course* cptr, Teacher* tptr)
{
    Content = content;
    CoursePTR = cptr;
    Createdby = tptr;
}



void OBE::SystemSetup()
{
    ReadEmployeesFromFile("Employee.txt");
    ReadProgramsFromFile("Program.txt");
    ReadCoursesFromFile("Course.txt");
    ReadPLOsFromFile("PLO.txt");
    ReadCLOsFromFile("CLO.txt");
    ReadTeachingsFromFile("Teaching.txt");
    ReadTopicsFromFile("Topic.txt");
    ReadEvaluationsFromFile("Evaluations.txt");
    ReadQuestionsFromFile("Questions.txt");
}
void OBE::SystemBackup()
{

    BackupEmployees("Employee.txt");
    BackupPrograms("Program.txt");
    BackupCourses("Course.txt");
    BackupPLOs("PLO.txt");
    BackupCLOs("CLO.txt");
    BackupTopics("Topic.txt");
    BackupEvals("Evaluations.txt");
    BackupQuestions("Questions.txt");
}

OBE* OBE::OBEExist = nullptr;

OBE* OBE::CreateOBE()
{
    if (OBEExist == nullptr)
    {
        OBEExist = new OBE;
    }
    return OBEExist;
}

Program* OBE::FindProgram(string id) { return FindObject(AllPrograms, id); }
Course* OBE::FindCourse(string id) { return FindObject(AllCourses, id); }
PLO* OBE::FindPLO(string id) { return FindObject(AllPLOs, id); }
CLO* OBE::FindCLO(string id) { return FindObject(AllCLOs, id); }
Employee* OBE::FindEmployee(string id) { return FindObject(AllEmployees, id); }

Employee* OBE::getCurrEmployee() { return CurrEmployee; }

void OBE::AddProgram(Program* ptr) { AllPrograms.push_back(ptr); }
void OBE::AddCourse(Course* ptr) { AllCourses.push_back(ptr); }
void OBE::AddPLO(PLO* ptr) { AllPLOs.push_back(ptr); }
void OBE::AddCLO(CLO* ptr) { AllCLOs.push_back(ptr); }
void OBE::AddEmployee(Employee* ptr) { AllEmployees.push_back(ptr); }

void OBE::SignUp()
{

    string newID;
    cout << "Enter ID of new Employee: ";
    cin >> newID;
    if (FindEmployee(newID) == nullptr)
    {
        if (newID[0] == 'A')
        {

            Employee* newAO = new AcademicOfficer;
            newAO->ReadDataFromUser(newID);
            AllEmployees.push_back(newAO);

            cout << newAO->GetID() << " Registered" << endl;
        }
        else if (newID[0] == 'T')
        {

            Employee* newAO = new Teacher;
            newAO->ReadDataFromUser(newID);
            AllEmployees.push_back(newAO);
            cout << newAO->GetID() << " Registered" << endl;
        }
        else
            cout << "Invalid ID" << endl;
    }
    else
        cout << "Employee already exists with id: " << newID << endl;
}
void OBE::LogIn()
{
    string logger;
    cout << "Enter your employee ID: ";
    cin >> logger;

    Employee* currUser = FindObject(AllEmployees, logger);
    if (currUser != nullptr)
    {
        OBE::CurrEmployee = currUser;
        cout << "User Logged in : ";
        currUser->Display();
    }
    else
        cout << "Employee does not exists with id: " << logger << endl;
}

void OBE::ListAllPrograms() { ListAllObjects(AllPrograms); }
void OBE::ListAllCourses() { ListAllObjects(AllCourses); }
void OBE::ListAllEmployees() { ListAllObjects(AllEmployees); }
void OBE::ListAllPLOs() { ListAllObjects(AllPLOs); }
void OBE::ListAllCLOs() { ListAllObjects(AllCLOs); }

void OBE::ReadEmployeesFromFile(string filename)
{
    ifstream EmployeeFile(filename);

    if (EmployeeFile.is_open())
    {
        int count = 0;
        EmployeeFile >> count;
        for (int i = 0; i < count; i++)
        {
            string id;
            EmployeeFile >> id;
            Employee* temp = nullptr;
            if (id[0] == 'A')
            {
                temp = new AcademicOfficer;
            }
            else if (id[0] == 'T')
            {
                temp = new Teacher;
            }

            temp->ReadDataFromFile(id, EmployeeFile);
            AddEmployee(temp);
        }
        
        EmployeeFile.close();
    }
    else
        cout << "ERROR :: FILE NOT OPENED" << endl;
}
void OBE::ReadProgramsFromFile(string fileName)
{
    ifstream ProgramFile(fileName);
    if (ProgramFile.is_open())
    {
        int count = 0;
        ProgramFile >> count;
        for (int i = 0; i < count; i++)
        {
            Program* temp = new Program;
            temp->ReadDataFromFile(ProgramFile);

            AddProgram(temp);
        }
        ProgramFile.close();
        
    }
    else
        cout << "ERROR :: FILE NOT OPENED" << endl;
}
void OBE::ReadCoursesFromFile(string fileName)
{
    ifstream CourseFile(fileName);
    if (CourseFile.is_open())
    {
        int count = 0;
        CourseFile >> count;
        for (int i = 0; i < count; i++)
        {
            Course* newOBJ = new Course;
            newOBJ->ReadDataFromFile(CourseFile);
            AddCourse(newOBJ);

            string pID;
            CourseFile >> pID;
            while (pID != "-1")
            {
                Program* ptr = FindProgram(pID);
                if (ptr != nullptr)
                {
                    ptr->AddCourse(newOBJ);
                    newOBJ->AddPrograms(ptr);
                }
                else
                    cout << "No program found with ID: " << pID << endl;

                CourseFile >> pID;
            }
            CourseFile.ignore();
        }
        CourseFile.close();
        

    }
    else
        cout << "ERROR :: FILE NOT OPENED" << endl;
}
void OBE::ReadPLOsFromFile(string filename)
{
    ifstream PLOFile("PLO.txt");

    if (PLOFile.is_open())
    {
        int count = 0;
        PLOFile>> count;
        for (int i = 0; i < count; i++)
        {
            PLO* temp = new PLO;
            temp->ReadDataFromFile(PLOFile);

            string pID;
            PLOFile >> pID;
            Program* tempProgram = FindProgram(pID);
            if (tempProgram != nullptr)
            {
                tempProgram->AddPLO(temp);
                temp->SetProgramPTR(tempProgram);
            }
            else
                cout << "No Program is offered with ID: " << pID << endl;

            AddPLO(temp);
        }
        PLOFile.close();
    }
    else
        cout << "ERROR :: FILE NOT OPENED" << endl;
}
void OBE::ReadCLOsFromFile(string filename)
{
    ifstream CLOFile("CLO.txt");

    if (CLOFile.is_open())
    {
        int count = 0;
        CLOFile >> count;
        for (int i = 0; i < count; i++)
        {
            CLO* newOBJ = new CLO;
            newOBJ->ReadDataFromFile(CLOFile);

            string parentplo;
            CLOFile >> parentplo;
            PLO* pPLO = FindPLO(parentplo);
            if (pPLO != nullptr)
            {
                newOBJ->SetParentPLO(pPLO);
                pPLO->AddCLO(newOBJ);
            }
            else
                cout << "No PLO found with ID: " << parentplo << endl;
            string C;
            CLOFile >> C;
            Course* CPtr = FindCourse(C);
            if (CPtr != nullptr)
            {
                CPtr->AddCLO(newOBJ);
                newOBJ->SetCoursePTR(CPtr);
            }
            else
                cout << "No Course found with ID: " << C << endl;

            AddCLO(newOBJ);
        }
        CLOFile.close();
    }
    else
        cout << "ERROR :: FILE NOT OPENED" << endl;
}
void OBE::ReadTeachingsFromFile(string filename)
{
    ifstream TeachingFile(filename);

    if (TeachingFile.is_open())
    {
        int count = -1;
        string c, t;
        TeachingFile >> count;
        for (int i = 0; i < count; i++)
        {
            Teaching* newOBJ = new Teaching;

            TeachingFile >> c;
            TeachingFile >> t;

            Course* cPtr = FindCourse(c);
            Teacher* tPtr = (Teacher*)FindEmployee(t);

            if (cPtr != nullptr)
            {
                newOBJ->SetCourse(cPtr);
            }
            else
            {
                cout << "Invalid Course ID" << endl;
                return;
            }
            if (tPtr != nullptr)
            {
                newOBJ->SetTeacher(tPtr);
            }
            else
            {
                cout << c << " " << t << endl;
                cout << "Invalid Teacher ID" << endl;
                return;
            }

            tPtr->AddTeaching(newOBJ);
            CourseRegistration.push_back(newOBJ);
        }
        TeachingFile.close();
    }
    else
        cout << "ERROR :: FILE NOT OPENED" << endl;
}
void OBE::ReadTopicsFromFile(string filename)
{
    ifstream FileaReader(filename);
    if (FileaReader.is_open())
    {
        int count = 0;
        string s;
        FileaReader >> count;
        for (int i = 0; i < count; i++)
        {
            FileaReader >> s;
            Teacher* tptr = (Teacher*)FindEmployee(s);

            tptr->AddTopicFromFile(FileaReader);
        }
    }
}
void OBE::ReadEvaluationsFromFile(string filename)
{
    ifstream fileReader(filename);
    //fileReader.open(filename);
    if (fileReader.is_open())
    {
        int count;
        fileReader >> count;
        for (int i = 0; i < count; i++)
        {
            string s;
            fileReader >> s;
            Teacher* Tptr = (Teacher*)FindEmployee(s);
            Tptr->ReadEvalsFromFile(fileReader);
        }
    }
}
void OBE::ReadQuestionsFromFile(string filename)
{
    ifstream fileReader(filename);
    if (fileReader.is_open())
    {
        int count;
        fileReader >> count;
        for (int i = 0; i < count; i++)
        {
            string s;
            fileReader >> s;
            Teacher* Tptr = (Teacher*)FindEmployee(s);
            Tptr->ReadQuestionsFromFile(fileReader);
        }
    }
}

bool OBE::RemoveProgram(string id)
{
    Program* ptr = FindProgram(id);
    if (ptr != nullptr)
    {
        return RemoveObjects(AllPrograms, ptr);
    }
    return false;
}
bool OBE::RemoveCourse(string id)
{
    Course* ptr = FindCourse(id);
    if (ptr != nullptr)
    {
        return RemoveObjects(AllCourses, ptr);
    }
    return false;
}
bool OBE::RemovePLO(string id)
{
    PLO* ptr = FindPLO(id);
    if (ptr != nullptr)
    {
        return RemoveObjects(AllPLOs, ptr);
    }
    return false;
}
bool OBE::RemoveCLO(string id)
{
    CLO* ptr = FindCLO(id);
    if (ptr != nullptr)
    {
        return RemoveObjects(AllCLOs, ptr);
    }
    return false;
}

void OBE::CLOReport()
{
    cout << "Enter CLO id to check if it is tested or not ?: ";
    string cl;
    cin >> cl;
    CLO* clo = FindCLO(cl);
    if (clo != nullptr)
    {
        if (clo->IsTested())
        {
            cout << clo->GetID() << " has been tested" << endl;
        }
        else
            cout << "This CLO has not been tested" << endl;
    }
    else
        cout << "Invalid CLO id" << endl;
}
void OBE::CLOsOfCourseReport()
{
    cout << "Enter Course id to check if its CLOs has been tested or not ?: ";
    string c;
    cin >> c;
    Course* Cptr = FindCourse(c);
    if (Cptr != nullptr)
    {
        bool flag = Cptr->CheckCLOTested();
        if (flag)
            cout << "All CLOs have been test" << endl;
        else
            cout << "All CLOs have not been test" << endl;
    }
    else
        cout << "Invalid Course id" << endl;
}
void OBE::CLOsOfPLO()
{
    cout << "Enter PLO id whos CLOs you want to see: ";
    string c;
    cin >> c;
    PLO* pl = FindPLO(c);
    if (pl != nullptr)
    {
        pl->ListCLOs();
    }
    else
        cout << "Invalid PLO id" << endl;
}

void OBE::ViewReports()
{
    int option = 0;

    while (option != -1)
    {
        (void)system("cls");
        cout << "Press 1: To Check whether a CLO has been tested or not (in two "
            "different questions)"
            << endl;
        cout << "Press 2: To Check whether all CLO's of a given course has been "
            "tested or not"
            << endl;
        cout
            << "Press 3:  For a given PLO, generate a list of all the relevant CLOs"
            << endl;
        cout << "Press -1: To exit" << endl;
        cout << "Enter Your Choice: ";
        cin >> option;

        switch (option)
        {
        case 1:
            CLOReport();
            break;
        case 2:
            CLOsOfCourseReport();
            break;
        case 3:
            CLOsOfPLO();
            break;
        case -1:
            return;

        default:
            cout << "Invalid Statement";
            break;
        }
        (void)system("pause");
    }
}
void OBE::MainMenu()
{
    int option = 0;
    while (option != -1)
    {

        (void)system("cls");
        cout << "==================================================" << endl;
        cout << "|                                                |" << endl;
        cout << "|                      .*.                       |" << endl;
        cout << "|                    WELCOME                     |" << endl;
        cout << "|                      TO                        |" << endl;
        cout << "|                   ~OBE SYSTEM~                 |" << endl;
        cout << "|                                                |" << endl;
        cout << "|                                                |" << endl;
        cout << "==================================================" << endl;
        cout << endl << endl;
        cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++" << endl;
        cout << "|  1:LogIn                                       |" << endl;
        cout << "|  2:SignUp                                      |" << endl;
        cout << "|  3:View Reports                                |" << endl;
        cout << "| -1:Exit                                        |" << endl;
        cout << "|  Select Your Desired Option:                   |" << endl;
        cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++" << endl;
        cin >> option;
        switch (option)
        {
        case 1:
            LogIn();
            return;
        case 2:
            SignUp();
            break;
        case 3:
            ViewReports();
            break;
        case -1:
            return;
        default:
            cout << "Invalid Option" << endl;
            break;
        }
        (void)system("pause");
    }
}

vector<Topic*> OBE::GetAllTopics()
{
    vector<Topic*> AllTopics;
    for (int i = 0; i < AllEmployees.size(); i++)
    {
        vector<Topic*> topicTeacher = AllEmployees[i]->GetTopics();
        for (int i = 0; i < topicTeacher.size(); i++)
        {
            AllTopics.push_back(topicTeacher[i]);
        }
    }
    return AllTopics;
}
vector<Evaluation*> OBE::GetAllEvals()
{
    vector<Evaluation*> AllEvals;
    for (int i = 0; i < AllEmployees.size(); i++)
    {
        vector<Evaluation*> evalTeacher = AllEmployees[i]->GetEvals();

        for (int i = 0; i < evalTeacher.size(); i++)
        {
            AllEvals.push_back(evalTeacher[i]);
        }
    }
    return AllEvals;
}
vector<Question*> OBE::GetAllQs()
{
    vector<Question*> AllQs;
    for (int i = 0; i < AllEmployees.size(); i++)
    {
        vector<Question*> curr = AllEmployees[i]->GetQuestions();
        for (int i = 0; i < curr.size(); i++)
        {
            AllQs.push_back(curr[i]);
        }
    }
    return AllQs;
}

void OBE::BackupEmployees(string filename)
{

    ifstream file(filename);
    int count;
    file >> count;
    if (count != AllEmployees.size()) // in case some new object has been added 
    {
        ofstream writer(filename);
        if (writer.is_open())
        {

            writer << AllEmployees.size();
            writer << "\n";
            for (int i = 0; i < AllEmployees.size(); i++)
            {
                AllEmployees[i]->WriteDataToFile(writer);
            }
            writer.close();
        }
    }
    file.close();
}
void OBE::BackupPrograms(string filename)
{
    ifstream file(filename);
    if (file.is_open())
    {
        int count;
        file >> count;
        ofstream writer(filename);
        if (writer.is_open())
        {
            writer << AllPrograms.size();
            writer << "\n";
            for (int i = 0; i < AllPrograms.size(); i++)
            {
                AllPrograms[i]->WriteDataToFile(writer);
            }
            writer.close();
        }
        file.close();
    }
}
void OBE::BackupCourses(string filename)
{
    ifstream file(filename);
    int count;
    file >> count;
    if (1)
    {
        ofstream writer(filename);
        if (writer.is_open())
        {
            writer << AllCourses.size();
            writer << "\n";
            for (int i = 0; i < AllCourses.size(); i++)
            {
                AllCourses[i]->WriteDataToFile(writer);
                //AllCourses[i]->WriteCLOsToFile(writer);
                AllCourses[i]->WriteProgramsToFile(writer);
            }
            writer.close();
        }
    }
    file.close();
}
void OBE::BackupPLOs(string filename)
{
    ifstream file(filename);
    int count;
    file >> count;
    file.close();
    if (1)
    {
        ofstream writer(filename);
        if (writer.is_open())
        {
            writer << AllPLOs.size();
            writer << "\n";
            for (int i = 0; i < AllPLOs.size(); i++)
            {
                AllPLOs[i]->WriteDataToFile(writer);
                writer << AllPLOs[i]->GetProgramPTR() << "\n";
            }
            writer.close();
        }
    }
}
void OBE::BackupCLOs(string filename)
{
    ifstream file(filename);
    int count;
    file >> count;
    file.close();
    if (1) // in case some new object has been added or
        // someone has been removed;
    {
        ofstream writer(filename);
        if (writer.is_open())
        {

            writer << AllCLOs.size() << "\n";
            for (int i = 0; i < AllCLOs.size(); i++)
            {
                AllCLOs[i]->WriteCLOtoFile(writer);
            }
            writer.close();
        }
    }
}
void OBE::BackupTopics(string filename)
{
    vector<Topic*> allTopics = GetAllTopics();

    ifstream check(filename);
    int count = 0;
    check >> count;
    check.close();

    if (1)
    {
        ofstream writer(filename);
        writer << allTopics.size() << "\n";
        for (int i = 0; i < allTopics.size(); i++)
        {
            allTopics[i]->BackupTopicToFile(writer);
        }
        writer.close();
    }
}
void OBE::BackupEvals(string filename)
{
    vector<Evaluation*> allevals = GetAllEvals();
    ifstream check(filename);
    int count = 0;
    check >> count;
    check.close();

    if (1)
    {
        ofstream writer(filename);
        writer << allevals.size() << "\n";
        for (int i = 0; i < allevals.size(); i++)
        {
            allevals[i]->BackupEvaluationToFile(writer);
        }
        writer.close();
    }
}
void OBE::BackupQuestions(string filename)
{
    ifstream check(filename);
    int count = 0;
    check >> count;
    check.close();

    vector<Question*> AllQs = GetAllQs();

    if (1)
    {

        ofstream writer(filename);
        writer << AllQs.size() << "\n";
        for (int i = 0; i < AllQs.size(); i++)
        {
            AllQs[i]->BackupQuestion(writer);
        }
        writer.close();
    }
}

vector<Topic*> Employee::GetTopics()
{
    vector<Topic*> topics;
    return topics;
}
vector<Evaluation*> Employee::GetEvals()
{
    vector<Evaluation*> topics;
    return topics;
}
vector<Question*> Employee::GetQuestions()
{
    vector<Question*> qs;
    return qs;
}

void AcademicOfficer::AddProgramFromUser()
{
    string newOBJ;
    cout << "Enter ID: ";
    cin >> newOBJ;
    OBE* OBE = OBE::CreateOBE();
    if (OBE->FindProgram(newOBJ) == nullptr)
    {
        Program* newPogram = new Program;
        newPogram->ReadDataFromUser(newOBJ);
        OBE->AddProgram(newPogram);
    }
    else
        cout << "Program Already Exits with this ID" << endl;
}
void AcademicOfficer::AddPLOFromUser()
{

    string newOBJ;
    cout << "Enter ID: ";
    cin >> newOBJ;
    OBE* OBE = OBE::CreateOBE();
    if (OBE->FindPLO(newOBJ) == nullptr)
    {
        PLO* newPLO = new PLO;
        newPLO->ReadDataFromUser(newOBJ);

        OBE->AddPLO(newPLO);

        // add to relevent program

        string t;
        cout << "Add program ID which covers this PLO: ";
        cin >> t;

        Program* ptr = OBE->FindProgram(t);

        if (ptr != nullptr)
        {
            ptr->AddPLO(newPLO);
            newPLO->SetProgramPTR(ptr);
        }
        else
            cout << "Invalid ProgramID" << endl;
    }
    else
        cout << "PLO Already Exits with this ID" << endl;
}
void AcademicOfficer::AddCourseFromUser()
{

    string newOBJ;
    cout << "Enter ID: ";
    cin >> newOBJ;
    OBE* OBE = OBE::CreateOBE();
    if (OBE->FindCourse(newOBJ) == nullptr)
    {
        Course* newCourse = new Course;
        newCourse->ReadDataFromUser(newOBJ);

        OBE->AddCourse(newCourse);

        string t;
        cout << "Add program ID which offers this course: ";
        cin >> t;

        Program* ptr = OBE->FindProgram(t);
        if (ptr != nullptr)
        {
            ptr->AddCourse(newCourse);
            newCourse->AddPrograms(ptr);
        }
        else
            cout << "Invalid ProgramID" << endl;
    }
    else
        cout << "Course Already Exits with this ID" << endl;
}
void AcademicOfficer::AddCLOFromUser()
{
    string newOBJ;
    cout << "Enter ID: ";
    cin >> newOBJ;
    OBE* OBE = OBE::CreateOBE();
    if (OBE->FindCLO(newOBJ) == nullptr)
    {

        CLO* newCLO = new CLO;
        newCLO->ReadDataFromUser(newOBJ);

        // add to relevant PLO
        string t;
        cout << "Add PLO ID which is satisfied by this CLO: ";
        cin >> t;

        PLO* plptr = OBE->FindPLO(t);
        if (plptr != nullptr)
        {
            plptr->AddCLO(newCLO);
            newCLO->SetParentPLO(plptr);
        }
        else
            cout << "Invalid PLO ID" << endl;

        // add to relevant course
        string t1;
        cout << "Add Course ID which covers this CLO: ";
        cin >> t1;

        Course* Cptr = OBE->FindCourse(t1);
        if (Cptr != nullptr)
            Cptr->AddCLO(newCLO);
        else
            cout << "Invalid PLO ID" << endl;
    }
}

void AcademicOfficer::AddEntities()
{
    int option = 0;

    while (option != -1)
    {
        system("cls");
        cout << "Academic Officer Logged in : ";
        Display();
        //cout << "AddEntities()" << endl;
        cout << "Press 1: To Add Program\n";
        cout << "Press 2: To Add Course\n";
        cout << "Press 3: To Add PLO\n";
        cout << "Press 4: To Add CLO\n";
        cout << "Press -1: To Exit\n";
        cout << "Please Enter Your Choice: ";

        cin >> option;
        switch (option)
        {
        case 1:
            AddProgramFromUser();
            break;
        case 2:
            AddCourseFromUser();
            break;
        case 3:
            AddPLOFromUser();
            break;
        case 4:
            AddCLOFromUser();
        case -1:
            return;

        default:
            cout << "Invalid Option";
            break;
        }
    }
}
void AcademicOfficer::UpdateEntities()
{
    int option = 0;

    while (option != -1)
    {
        (void)system("cls");
        //cout << "UpdateEntities()" << endl;
        cout << "Academic Officer Logged in : ";
        Display();
        cout << "Press 1: To Update Program\n";
        cout << "Press 2: To Update Course\n";
        cout << "Press 3: To Update PLO\n";
        cout << "Press 4: To Update CLO\n";
        cout << "Press -1: To Exit\n";
        cout << "Please Enter Your Choice: ";

        cin >> option;
        if (option == -1)
            return;

        string s;
        cout << "Enter entity ID you want to update: ";
        cin >> s;

        Entity* ptr = nullptr;
        OBE* obe = OBE::CreateOBE();
        switch (option)
        {
        case 1:

            ptr = obe->FindProgram(s);
            if (ptr != nullptr)
                ptr->UpdateEnity();
            else
                cout << "No program found with this ID" << endl;

            break;
        case 2:
            ptr = obe->FindCourse(s);
            if (ptr != nullptr)
                ptr->UpdateEnity();
            else
                cout << "No course found with this ID" << endl;

            break;
        case 3:
            ptr = obe->FindPLO(s);
            if (ptr != nullptr)
                ptr->UpdateEnity();
            else
                cout << "No PLO found with this ID" << endl;

            break;
        case 4:
            ptr = obe->FindCLO(s);
            if (ptr != nullptr)
                ptr->UpdateEnity();
            else
                cout << "No CLO found with this ID" << endl;

            break;

        case -1:
            return;

        default:
            cout << "Invalid Option";
            break;
        }
        system("pause");
    }
}
void AcademicOfficer::RemoveEntities()
{
    int option = 0;

    while (option != -1)
    {
        (void)system("cls");
        cout << "Academic Officer Logged in : ";
        Display();
        //cout << "RemoveEntities()" << endl;
        cout << "Press 1: To Remove Program\n";
        cout << "Press 2: To Remove Course\n";
        cout << "Press 3: To Remove PLO\n";
        cout << "Press 4: To Remove CLO\n";
        cout << "Press -1: To Exit\n";

        cout << "Please Enter Your Choice: ";

        cin >> option;
        if (option == -1)
            return;
        OBE* obe = OBE::CreateOBE();

        string s;
        cout << "Enter entity ID you want to remove: ";
        cin >> s;

        switch (option)
        {
        case 1:
            if (obe->RemoveProgram(s))
                cout << s << " removed successfull" << endl;
            else
                cout << s << " not removes" << endl;

            break;
        case 2:
            if (obe->RemoveCourse(s))
                cout << s << " removed successfull" << endl;
            else
                cout << s << " not removes" << endl;

            break;
        case 3:
            if (obe->RemovePLO(s))
                cout << s << " removed successfull" << endl;
            else
                cout << s << " not removes" << endl;
            break;
        case 4:
            if (obe->RemoveCLO(s))
                cout << s << " removed successfull" << endl;
            else
                cout << s << " not removes" << endl;

            break;

        case -1:
            return;

        default:
            cout << "Invalid Option";
            break;
        }
        system("pause");
    }
}
void AcademicOfficer::EmployeeMenu()
{
    int option = 0;

    while (option != -1)
    {
        (void)system("cls");
        //cout << "EmployeeMenu()" << endl;
        cout << "Academic Officer Logged in : ";
        Display();
        cout << "Press 1: To Add New Entity\n";
        cout << "Press 2: To Update any Entity\n";
        cout << "Press 3: To Delete any Entity\n";
        cout << "Press -1: To exit\n";

        cout << "Please Enter Your Choice: ";
        cin >> option;

        switch (option)
        {
        case 1:
            AddEntities();
            break;
        case 2:
            UpdateEntities();
            break;
        case 3:
            RemoveEntities();
            break;
        case -1:
            return;

        default:
            cout << "Invalid Option";
            break;
        }
        system("pause");
    }
}

void Teaching::SetTeacher(Employee* ptr) { TeacherPTR = ptr; }
void Teaching::SetCourse(Course* ptr) { CoursePTR = ptr; }
Course* Teaching::GetCourse() { return CoursePTR; }
vector<CLO*> Teaching::GetCLOs() { return CoursePTR->GetCLOs(); }

void Teacher::AddTeaching(Teaching* ptr) { AllCoursesAssigned.push_back(ptr); }
void Teacher::AddTopicFromFile(ifstream& fileReader)
{

    string cID;
    fileReader >> cID;
    Course* Cptr = FindAssignedCourse(cID);
    if (Cptr == nullptr)
    {
        cout << "No course assigned to you with this ID" << endl;
        return;
    }
    fileReader.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(fileReader, cID);
    Topic* newOBJ = new Topic(cID, Cptr, this);
    TopicsCovered.push_back(newOBJ);
}
void Teacher::ReadEvalsFromFile(ifstream& fileReader)
{
    Evaluation* newOBJ = new Evaluation;
    newOBJ->ReadDataFromFile(fileReader);

    string cl;
    while (cl != "-1")
    {
        fileReader >> cl;
        CLO* clptr = FindObject(GetCLOsOfCourses(), cl);
        if (clptr != nullptr)
        {
            newOBJ->AddCLO(clptr);
            newOBJ->SetTeacherPTR(this);
        }
    }
    Evaluations.push_back(newOBJ);
}
void Teacher::ReadQuestionsFromFile(ifstream& fileReader)
{
    string s;
    fileReader >> s;
    Evaluation* evptr = FindObject(Evaluations, s);
    evptr->ReadQuestionsFromFile(fileReader);
}

void Teacher::AddTopicFromUser()
{
    string cID, s2;
    cout << "Enter course ID: ";
    cin >> cID;
    Course* Cptr = FindAssignedCourse(cID);
    if (Cptr == nullptr)
    {
        cout << "No course assigned to you with this ID" << endl;
        return;
    }
    cout << "Enter Content: \n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, s2);

    Topic* newObj = new Topic(s2, Cptr, this);

    TopicsCovered.push_back(newObj);
}
void Teacher::AddEvalsFromUser()
{

    Evaluation* newObj = new Evaluation;
    string id;
    cout << "Enter Evaluation ID: ";
    cin >> id;
    if (FindObject(Evaluations, id) == nullptr)
    {
        newObj->ReadDataFromUser(id);
    }

    vector<CLO*> AssociatedCLOs = GetCLOsOfCourses();
    ListAllObjects(AssociatedCLOs);
    string clID;
    while (clID != "-1")
    {
        cout << "Enter CLO ID you want to cover in this evaluation\nOr Enter -1 to "
            "exit: ";
        cin >> clID;
        if (clID == "-1")
            return;

        CLO* CLOid = FindObject(AssociatedCLOs, clID);
        if (CLOid != nullptr)
        {
            newObj->AddCLO(CLOid);
        }
        else
            cout << "Invalid CLO ID" << endl;
    }
    char op;
    while (1)
    {
        cout << "Do you want to enter Question for this Evaluation: [y/n]";
        cin >> op;
        if (op == 'y' || op == 'Y')
        {
            newObj->AddQuestionFromUser();
        }
        else if (op == 'n' || op == 'N')
            return;
    }

    Evaluations.push_back(newObj);
}
void Teacher::AddQuestionFromUser()
{

    if (Evaluations.size() > 0)
    {
        string evID;
        cout << "Enter Evaluation ID for which you want to enter Question: ";
        Evaluation* evalID = FindObject(Evaluations, evID);

        if (evalID != nullptr)
        {
            evalID->AddQuestionFromUser();
        }
        cout << "No evaluation found with this ID" << endl;
    }
    else
        cout << "There are no evaluations created yet. Please Create Evaluations "
        "before adding questions into it"
        << endl;
}

void Teacher::UpdateTopic()
{
    if (TopicsCovered.size() > 0)
    {

        cout << "Total Topics" << TopicsCovered.size() << endl;
        cout << "Enter topic number you want to update: ";
        int opt;
        cin >> opt;
        opt -= 1;

        if (opt >= 0 && opt < TopicsCovered.size())
        {
            TopicsCovered[opt]->UpdateContent();
        }
        else
            cout << "Invalid Topic Number" << endl;
    }
    cout << "No topics to update" << endl;
}
void Teacher::UpdateEvaluation()
{
    if (Evaluations.size() > 0)
    {

        cout << "Enter Evaluation ID you want to update: ";
        string evID;
        Evaluation* ev = FindObject(Evaluations, evID);
        if (ev != nullptr)
        {
            ev->UpdateEnity();
        }
        else
            cout << "Invalid Evaluation ID eneterd";
    }
    else
        cout << "No evaluations to update" << endl;
}
void Teacher::UpdateQuestion()
{
    if (Evaluations.size() > 0)
    {
        cout << "Enter Evaluation ID whose question you want to update: ";
        string ev;
        cin >> ev;

        Evaluation* evID = FindObject(Evaluations, ev);
        if (evID != nullptr)
        {
            evID->UpdateQuestion();
        }
    }
}

void Teacher::RemoveTopic()
{
    if (TopicsCovered.size() > 0)
    {
        cout << "Total Topics: " << TopicsCovered.size();
        cout << "Enter topic Number you want to remove: ";
        int opt;
        cin >> opt;
        opt -= 1;
        if (opt >= 0 && opt < TopicsCovered.size())
        {
            RemoveObjects(TopicsCovered, TopicsCovered[opt]);
        }
        else
            cout << "Invalid Topic Number" << endl;
    }
    else
        cout << "No topics to remove" << endl;
}
void Teacher::RemoveEvaluation()
{
    if (Evaluations.size() > 0)
    {
        cout << "Enter Evaluation ID you want to remove: ";
        string evID;
        cin >> evID;
        Evaluation* ev = FindObject(Evaluations, evID);
        if (ev != nullptr)
        {
            RemoveObjects(Evaluations, ev);
        }
        else
            cout << "Invalid Evaluatio ID" << endl;
    }
    else
        cout << "No evaluation to remove" << endl;
}
void Teacher::RemoveQuestion()
{
    if (Evaluations.size() > 0)
    {
        cout << "Enter Evaluation ID whose question you want to remove: ";
        string evID;
        cin >> evID;
        Evaluation* ev = FindObject(Evaluations, evID);
        if (ev != nullptr)
        {
            ev->RemoveQuestion();
        }
        else
            cout << "Invalid Evaluatio ID" << endl;
    }
    else
        cout << "No evaluation to remove question from" << endl;
}

void Teacher::UpdateItem()
{
    int option = 0;

    while (option != -1)
    {
        (void)system("cls");

        cout << "User Logged in : ";
        Display();

        cout << "Press 1:  To update Topic" << endl;
        cout << "Press 2:  To update Evaluation" << endl;
        cout << "Press 3:  To update Question of an evaluation" << endl;
        cout << "Press -1: To exit" << endl;

        cout << "Please Enter Your Choice: ";
        cin >> option;

        switch (option)
        {
        case 1:
            UpdateTopic();
            break;
        case 2:
            UpdateEvaluation();
            break;
        case 3:
            UpdateQuestion();
            break;
        case -1:
            return;

        default:
            cout << "Invalid Option";
            break;
        }
        (void)system("pause");
    }
}
void Teacher::RemoveItem()
{
    int option = 0;

    while (option != -1)
    {
        (void)system("cls");
        cout << "User Logged in : ";
        Display();
        cout << "Press 1:  To Remove a Topic" << endl;
        cout << "Press 2:  To Remove a Evaluation" << endl;
        cout << "Press 3:  To Remove a Question of an evaluation" << endl;
        cout << "Press -1: To exit" << endl;

        cout << "Please Enter Your Choice: ";
        cin >> option;

        switch (option)
        {
        case 1:
            RemoveTopic();
            break;
        case 2:
            RemoveEvaluation();
            break;
        case 3:
            RemoveQuestion();
            break;
        case -1:
            return;

        default:
            cout << "Invalid Option";
            break;
        }
        (void)system("pause");
    }
}
void Teacher::AddItem()
{
    int option = 0;

    while (option != -1)
    {
        (void)system("cls");
        cout << "User Logged in : ";
        Display();
        cout << "Press 1:  To Add New Topic" << endl;
        cout << "Press 2:  To Add New Evaluation" << endl;
        cout << "Press 3:  To Add New Question to an evaluation" << endl;
        cout << "Press -1: To exit" << endl;

        cout << "Please Enter Your Choice: ";
        cin >> option;

        switch (option)
        {
        case 1:
            AddTopicFromUser();
            break;
        case 2:
            AddEvalsFromUser();
            break;
        case 3:
            AddQuestionFromUser();
            break;
        case -1:
            break;

        default:
            cout << "Invalid Option";
            break;
        }
        (void)system("pause");
    }
}

vector<Topic*> Teacher::GetTopics() { return TopicsCovered; }
vector<Evaluation*> Teacher::GetEvals() { return Evaluations; }

void Teacher::EmployeeMenu()
{
    int option = 0;

    while (option != -1)
    {
        (void)system("cls");
        cout << "User Logged in : ";
        Display();
        cout << "Press 1:  To Add item" << endl;
        cout << "Press 2:  To Update item" << endl;
        cout << "Press 3:  To Remove item" << endl;
        cout << "Press -1: To exit" << endl;

        cout << "Please Enter Your Choice: ";
        cin >> option;

        switch (option)
        {
        case 1:
            AddItem();
            break;
        case 2:
            UpdateItem();
            break;
        case 3:
            RemoveItem();
            break;
        case -1:
            return;

        default:
            cout << "Invalid Option";
            break;
        }
        (void)system("pause");
    }
}

vector<Question*> Teacher::GetQuestions()
{
    vector<Question*> AllQuestions;

    for (int i = 0; i < Evaluations.size(); i++)
    {
        vector<Question*> Qs = Evaluations[i]->GetAllQuestions();
        for (int i = 0; i < Qs.size(); i++)
        {
            AllQuestions.push_back(Qs[i]);
        }
    }
    return AllQuestions;
}
Course* Teacher::FindAssignedCourse(string id)
{
    for (int i = 0; i < AllCoursesAssigned.size(); i++)
    {
        Course* ptr = AllCoursesAssigned[i]->GetCourse();
        if (ptr->GetID() == id)
        {
            return ptr;
        }
    }
    return nullptr;
}
vector<CLO*> Teacher::GetCLOsOfCourses()
{
    vector<CLO*> AllCLOsRegistered;
    for (int i = 0; i < AllCoursesAssigned.size(); i++)
    {
        vector<CLO*> ithCLO = AllCoursesAssigned[i]->GetCLOs();
        for (int i = 0; i < ithCLO.size(); i++)
        {
            AllCLOsRegistered.push_back(ithCLO[i]);
        }
    }
    return AllCLOsRegistered;
}

void Evaluation::AddCLO(CLO* ptr)
{
    if (CheckExistence(CoveredCLOs, ptr) == false)
    {
        CoveredCLOs.push_back(ptr);
    }
    else
        cout << "CLO already added into this evaluation." << endl;
}
void Evaluation::AddQuestionFromUser()
{
    Question* newOBJ = new Question;

    newOBJ->SetContent();

    string clid;
    cout << "Enter CLO for this Question: ";
    cin >> clid;
    CLO* CLptr = FindObject(CoveredCLOs, clid);
    if (CLptr != nullptr)
    {
        newOBJ->SetCLO(CLptr);
        Questions.push_back(newOBJ);
    }
}
void Evaluation::ReadQuestionsFromFile(ifstream& fileReader)
{
    Question* newOBJ = new Question;
    newOBJ->SetContent(fileReader);

    string s;
    fileReader >> s;
    CLO* clptr = FindObject(CoveredCLOs, s);
    if (clptr != nullptr)
    {
        newOBJ->SetCLO(clptr);
        newOBJ->SetEvalID(this);
        newOBJ->SetTeacher(this->Assignedby);
        Questions.push_back(newOBJ);
    }
}
void Evaluation::UpdateQuestion()
{
    if (Questions.size() > 0)
    {
        cout << "Total Questions" << Questions.size() << endl;
        cout << "Enter Question number you want to update: ";
        int opt;
        cin >> opt;
        opt -= 1;

        if (opt >= 0 && opt < Questions.size())
        {
            Questions[opt]->UpdateContent();
        }
        else
            cout << "Invalid question Number" << endl;
    }
    else
        cout << "No question to update" << endl;
}
void Evaluation::RemoveQuestion()
{
    if (Questions.size() > 0)
    {
        cout << "Total Questions" << Questions.size() << endl;
        cout << "Enter Question number you want to remove: ";
        int opt;
        cin >> opt;
        opt -= 1;

        if (opt >= 0 && opt < Questions.size())
        {
            RemoveObjects(Questions, Questions[opt]);
        }
        else
            cout << "Invalid question Number" << endl;
    }
    else
        cout << "No question to update" << endl;
}
void Evaluation::SetTeacherPTR(Teacher* ptr) { Assignedby = ptr; }
void Evaluation::BackupEvaluationToFile(ofstream& writer)
{
    writer << Assignedby->GetID() << "\n";
    WriteDataToFile(writer);
    for (int i = 0; i < CoveredCLOs.size(); i++)
    {
        writer << CoveredCLOs[i]->GetID() << " ";
    }
    writer << -1;
}
vector<Question*> Evaluation::GetAllQuestions() { return Questions; }

void Topic::Display()
{
    cout << Content << " is covered under " << CoursePTR->GetID() << endl;
}
void Topic::UpdateContent()
{
    cout << "Enter updated content:" << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, Content);
}
void Topic::BackupTopicToFile(ofstream& writer)
{
    writer << Createdby->GetID() << "\n";
    writer << CoursePTR->GetID() << "\n";
    writer << Content << "\n";
}

void Question::SetContent()
{
    cout << "Enter Question: " << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, Content);
}
void Question::SetContent(ifstream& filereader)
{
    filereader.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(filereader, Content);
}
void Question::SetCLO(CLO* ptr)
{
    coveredCLO = ptr;
    ptr->AddQuestion(this);
}
void Question::SetTeacher(Teacher* ptr) { AskedBy = ptr; }
void Question::UpdateContent()
{
    cout << "Enter updated content:" << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, Content);
}
void Question::SetEvalID(Evaluation* ptr) { EvalID = ptr; }
void Question::BackupQuestion(ofstream& writer)
{
    writer << AskedBy->GetID() << "\n";
    writer << EvalID->GetID() << "\n";
    writer << Content << "\n";
    writer << coveredCLO->GetID() << "\n";
}


Program::~Program() {
    Deallocation(PLOs);
    Deallocation(OfferedCourses);
}
Course::~Course() {
    Deallocation(AllTeachersAssigned);
    Deallocation(CLOs);
    IsOfferedBy.clear();
}
PLO::~PLO() {
    this->BelongsTo = nullptr;
    //Deallocation(SatisfiedBy);
}
CLO::~CLO() {
    BelongsTo = nullptr;
    ParentPLO = nullptr;
    //Deallocation(TestedBy);
}

Evaluation::~Evaluation() {
    this->Assignedby = nullptr;
    CoveredCLOs.clear();
    Deallocation(Questions);
}
Question::~Question() {
    EvalID->RemoveQuestion(this);
    coveredCLO->RemoveQuestion(this);
    AskedBy = nullptr;

}