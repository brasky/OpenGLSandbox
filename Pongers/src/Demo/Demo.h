#pragma once

#include <functional>
#include <vector>
#include <string>
#include <iostream>
#include <Renderer.h>

namespace demo 
{
    class Demo
    {
    public:
        Demo() {}
        virtual ~Demo() {}
        virtual void OnUpdate(float deltaTime) {}
        virtual void OnRender() {}
        virtual void OnImGuiRender() {}
    };

    class DemoMenu : public Demo
    {
    public:
        DemoMenu(Demo*& currentDemoPointer);

        void OnImGuiRender() override;

        template<typename T>
        void RegisterDemo(const std::string& name)
        {
            std::cout << "Registering demo " << name << std::endl;
            m_Demos.push_back(std::make_pair(name, []() { return new T(); }));
        }

        template<typename T>
        void RegisterDemo(const std::string& name, Renderer& renderer)
        {
            std::cout << "Registering demo " << name << std::endl;

            m_Demos.push_back(std::make_pair(name, [&renderer]() 
                { return new T(std::forward<Renderer&>(renderer)); }));
        }
    private:
        Demo*& m_CurrentDemo;
        std::vector<std::pair<std::string, std::function<Demo*()>>> m_Demos;
    };
}