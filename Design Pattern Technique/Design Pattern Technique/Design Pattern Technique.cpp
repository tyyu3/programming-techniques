// Design Pattern Technique.cpp : Defines the entry point for the application.
//

#include "Design Pattern Technique.h"
#include "TextEditor.h"

using namespace std;

void DriverCode(const factory::AbstractFactory& factory)
{
    factory::AbstractTextBox* tb = factory.CreateTextBox();
    factory::AbstractPopup* pu = factory.CreatePopup();
    tb->MoveRight();
    tb->Input();
    tb->MoveRight();
    tb->Input();
    pu->ShowInfo();
    tb->MoveLeft();
    tb->Input();
    pu->ShowInfo(*tb);
    delete tb;
    delete pu;
}

int main()
{
    std::cout << "User: testing english driver:\n";
    factory::EnglishFactory* f1 = new factory::EnglishFactory();
    DriverCode(*f1);
    delete f1;
    std::cout << "\n";
    std::cout << "User: testing italian driver:\n";
    factory::ItalianFactory* f2 = new factory::ItalianFactory();
    DriverCode(*f2);
    delete f2;
    std::cout << "\n";
	return 0;
}
