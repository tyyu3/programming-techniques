#pragma once
#include <iostream>
#include <string>
#include <vector>
namespace factory
{
constexpr size_t len = 50;

class AbstractTextBox
{
public:
    virtual void MoveRight() = 0;
    virtual void MoveLeft() = 0;
    virtual void Input() = 0;

    virtual void DrawBox() const = 0;
};

class ItalianTextBox : public AbstractTextBox
{
public:
    void MoveRight() override
    {
        position = (position + 1) % len;
        DrawBox();
    }
    void MoveLeft() override
    {
        position = (position + len - 1) % len;
        DrawBox();
    }
    void Input() override
    {
        char sym;
        std::cin >> sym;
        content[position] = sym;
        DrawBox();
    }
    void DrawBox() const override
    {
        std::cout << "+";
        std::cout << "---";
        std::cout << name;
        for (int i = 0; i < len - name.size() - 3; ++i)
        {
            std::cout << "-";
        }
        std::cout << "+\n";
        std::cout << "|";
        for (int i = 0; i < len; ++i)
        {
            std::cout << content[i];
        }
        std::cout << "|\n";
        std::cout << "+";
        for (int i = 0; i < len; ++i)
        {
            if (i == position)
                std::cout << "^";
            else
                std::cout << "-";
        }
        std::cout << "+\n";
    }

private:
    const std::string name = "Casella Di Testo Italiana";
    size_t position = 0;
    std::vector<char> content = std::vector<char>(len, ' ');
};

class EnglishTextBox : public AbstractTextBox
{
public:
    void MoveRight() override
    {
        position = (position + 1) % len;
        DrawBox();
    }
    void MoveLeft() override
    {
        position = (position + len - 1) % len;
        DrawBox();
    }
    void Input() override
    {
        char sym;
        std::cin >> sym;
        content[position] = sym;
        DrawBox();
    }

    void DrawBox() const override
    {
        std::cout << "+";
        std::cout << "~~~";
        std::cout << name;
        for (int i = 0; i < len - name.size() - 3; ++i)
        {
            std::cout << "~";
        }
        std::cout << "+\n";
        std::cout << "|";
        for (int i = 0; i < len; ++i)
        {
            std::cout << content[i];
        }
        std::cout << "|\n";
        std::cout << "+";
        for (int i = 0; i < len; ++i)
        {
            if (i == position)
                std::cout << "^";
            else
                std::cout << "~";
        }
        std::cout << "+\n";
    }

private:
    const std::string name = "English Text Box";
    size_t position = 0;
    std::vector<char> content = std::vector<char>(len, ' ');
};
class AbstractPopup
{
public:
    virtual void ShowInfo() const = 0;
    virtual void ShowInfo(const AbstractTextBox& collaborator) const = 0;
};
class ItalianPopup : public AbstractPopup
{
public:
    void ShowInfo(const AbstractTextBox& collaborator) const override
    {
        std::cout << "-Informazioni in Italiano-\n";
        std::cout << "Queste sono informazioni in italiano e solo in italiano.\n";
        std::cout << "Lo stato corrente della casella di testo e:\n";
        collaborator.DrawBox();
    }
    void ShowInfo() const override
    {
        std::cout << "-Informazioni in Italiano-\n";
        std::cout << "Queste sono informazioni in italiano e solo in italiano.\n";
        std::cout << "Lo stato corrente della casella di testo e sconosciuto\n";
    }
};
class EnglishPopup : public AbstractPopup
{
public:
    void ShowInfo(const AbstractTextBox& collaborator) const override
    {
        std::cout << "-Info in English-\n";
        std::cout << "This is the info in english and only in english.\n";
        std::cout << "The current state of the textbox is:\n";
        collaborator.DrawBox();
    }
    void ShowInfo() const override
    {
        std::cout << "-Info in English-\n";
        std::cout << "This is the info in english and only in english.\n";
        std::cout << "The current state of the textbox is unknown\n ";
    }
};

class AbstractFactory
{
public:
    virtual AbstractTextBox* CreateTextBox() const = 0;
    virtual AbstractPopup* CreatePopup() const = 0;
};
class EnglishFactory : public AbstractFactory
{
    AbstractTextBox* CreateTextBox() const override
    {
        return new EnglishTextBox();
    }
    AbstractPopup* CreatePopup() const override
    {
        return new EnglishPopup();
    }
};
class ItalianFactory : public AbstractFactory
{
    AbstractTextBox* CreateTextBox() const override
    {
        return new ItalianTextBox();
    }
    AbstractPopup* CreatePopup() const override
    {
        return new ItalianPopup();
    }
};
}