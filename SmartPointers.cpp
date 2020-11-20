#include <iostream>
#include <memory>

class Smart
{
public:
    Smart()
    {
        std::cout << "created Smart\n";
    }

    ~Smart()
    {
        std::cout << "deleted Smart" << std::endl;
    }

    void Print() {}
};

int main()
{
    // Creating a unique and shared ptr in a scope.
    {
        // Copies Sharedsmart, however has no reference to it so Sharedsmart is deleted before it is reached.
        std::weak_ptr<Smart> eb;
        {
            // Sharedsmart is deleted here since ea holds a reference to it.
            std::shared_ptr<Smart> ea;
            {
                // Allocate my entity Smart. Smart in template argument. "smart" as name. No copying of unique pointers.
                std::unique_ptr<Smart> smart = std::make_unique<Smart>();
                smart->Print();

                /* Shared pointers work via reference counting (keeps track of how many references your pointers have.
                When reference count reaches zero it is deleted. */
                std::shared_ptr<Smart> sharedSmart = std::make_shared<Smart>();
                // The shared pointer is still alive til ea dies. Even if sharedSmart is deleted, ea lives.
                ea = sharedSmart;
                eb = sharedSmart;
            }
        }
    }
}