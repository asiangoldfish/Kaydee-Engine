#ifndef __ENTRY_POINT_H__
#define __ENTRY_POINT_H__

extern Kaydee::Application* Kaydee::createApplication(); 

int main(int arcg, char **argv)
{
    auto app = Kaydee::createApplication();
    app->print();
    app->run();
    delete app;
}

#endif