#include<iostream>
#include<memory>
#include<vector>
#include<string>

template<typename T>
class Tab {
public:
    std::string url;
    std::string name;
    T memory;
    Tab* next;
    Tab* prev;

    Tab(std::string u, std::string n, T m) : url(u), name(n), memory(m), next(nullptr), prev(nullptr) {}
};

template<typename T>
class Browser {
public:
    Tab<T>* head;
    Tab<T>* tail;
    Tab<T>* current;
    std::vector<std::pair<std::string, std::string>> bookmarks;

    Browser() : head(nullptr), tail(nullptr), current(nullptr) {}

    void addNewTab(const std::string& url, const std::string& name, T memory) {
        // Create a new tab node
        Tab<T>* newTab = new Tab<T>(url, name, memory);

        if (!head) {
            head = newTab;
            tail = newTab;
        } else {
            tail->next = newTab;
            newTab->prev = tail;
        }
        
        current = newTab;
    }

    void switchToPrevTab() {
        if (current && current->prev) {
            current = current->prev;
            std::cout << "Switch to previous tab = "
                      << "URL: " << current->url
                      << ", Name: " << current->name
                      << ", Memory: " << current->memory << "MB" << std::endl;
        } else {
            std::cout << "No previous tab" << std::endl;
        }
    }

    void switchToNextTab() {
        if (current && current->next) {
            current = current->next;
            std::cout << "Switch to next tab = "
                      << "URL: " << current->url
                      << ", Name: " << current->name
                      << ", Memory: " << current->memory << "MB" << std::endl;
        } else {
            std::cout << "No next tab" << std::endl;
        }
    }

    void closeCurrentTab() {
        if (!current) {
            std::cout << "There is no current tab to close." << std::endl;
            return;
        }

        Tab<T>* nextTab = current->next;
        Tab<T>* prevTab = current->prev;

        if (prevTab) {
            prevTab->next = nextTab;
        } else {
            head = nextTab;
        }
        
        if (nextTab) {
            nextTab->prev = prevTab;
        } else {
            tail = prevTab;
        }

        std::cout << "Closing tab: " << current->name << std::endl;
        delete current;

        if (nextTab) {
            current = nextTab;
        } else {
            current = prevTab;
        }

        if (current) {
            std::cout << "Now the current tab is = " << current->name << std::endl;
        } else {
            std::cout << "No tabs are open." << std::endl;
        }
    }

    void bookmarkCurrent() {
    if (!current) {
        std::cout << "There is no current tab to bookmark." << std::endl;
        return;
    }

    std::pair<std::string, std::string> bookmark(current->name, current->url);

    // Replace std::find with a manual loop to check for existing bookmark
    bool isBookmarked = false;
    for (const auto& b : bookmarks) {
        if (b.first == bookmark.first && b.second == bookmark.second) {
            isBookmarked = true;
            break;
        }
    }

    if (isBookmarked) {
        std::cout << "The bookmark is already added!" << std::endl;
    } else {
        bookmarks.push_back(bookmark);
        std::cout << "Bookmark added for: " << current->name << std::endl;
    }
}

    void showBookmarkTab() {
        std::cout << "Bookmarks: " << std::endl;
        for (const auto& bookmark : bookmarks) {
            std::cout << bookmark.first << "(" << bookmark.second << ")" << std::endl;
        }
    }

    void moveCurrentToFirst() {
        if (!current) {
            std::cout << "There is no current tab to move." << std::endl;
            return;
        }
        if (current == head) {
            std::cout << "The current tab is already the first tab." << std::endl;
            return;
        }

        if (current->next) {
            current->next->prev = current->prev;
        }
        if (current->prev) {
            current->prev->next = current->next;
        }

        if (current == tail) {
            tail = current->prev;
        }

        current->prev = nullptr;
        current->next = head;
        if (head) {
            head->prev = current;
        }
        head = current;

        if (!tail) {
            tail = current;
        }
    }

    T total_memory() {
        T totalMemory = T();
        Tab<T>* currentTab = head;

        while (currentTab != nullptr) {
            totalMemory += currentTab->memory;
            currentTab = currentTab->next;
        }

        return totalMemory;
    }

    void deleteTab() {
        if (!head) {
            std::cout << "There are no tabs to delete." << std::endl;
            return;
        }

        Tab<T>* toDelete = head;
        Tab<T>* iterator = head->next;

        while (iterator != nullptr) {
            if (iterator->memory > toDelete->memory) {
                toDelete = iterator;
            }
            iterator = iterator->next;
        }

        // Output the details of the tab to be deleted
        std::cout << "Deleted element = " << toDelete->name
                  << " with memory size = " << toDelete->memory << "MB" << std::endl;

        // Remove the tab from the list
        if (toDelete->prev) {
            toDelete->prev->next = toDelete->next;
        } else {
            // toDelete is the head
            head = toDelete->next;
        }
        if (toDelete->next) {
            toDelete->next->prev = toDelete->prev;
        } else {
            // toDelete is the tail
            tail = toDelete->prev;
        }

        // Update the current pointer if necessary
        if (toDelete == current) {
            current = toDelete->next ? toDelete->next : toDelete->prev;
        }

        // Finally, delete the tab
        delete toDelete;
    }

    void display(){
            auto curr = head;
            std::cout<<"Browser tab list = "<<std::endl;
            while(curr){
                std::cout<<"| "<<curr->name<<"  x|-->";
                curr = curr->next;
            }
            std::cout<<std::endl;
            std::cout<<std::endl;
        }
};

int main(){
    
    /*Browser<double> b1;
    b1.addNewTab("https://www.google.com","Google",23.45);
    b1.display();
    std::cout<<"Switch to previous tab = "<<std::endl;
    b1.switchToPrevTab();
    std::cout<<"Switch to Next tab = "<<std::endl;
    b1.switchToNextTab();
    b1.addNewTab("https://www.youtube.com","YouTube",56);
    b1.bookmarkCurrent();
    b1.display();
    b1.addNewTab("https://www.geeksforgeeks.com","GeeksForGeeks",45.78);
    b1.bookmarkCurrent();
    b1.addNewTab("https://chat.openai.com","ChatGPT",129);
    b1.addNewTab("https://linkedin.com","LinkedIn",410);
    b1.bookmarkCurrent();
    b1.addNewTab("https://github.com","Github",110);
    b1.addNewTab("https://kaggle.com","Kaggle",310);
    b1.bookmarkCurrent();
    b1.display();
    std::cout<<"Total memory consumption = "<<b1.total_memory()<<"MB"<<std::endl;
    b1.showBookmarkTab();
    b1.moveCurrentToFirst();
    b1.display();
    b1.deleteTab();
    b1.display();
    std::cout<<"Switch to next tab = "<<std::endl;
    b1.switchToNextTab();
    std::cout<<"Switch to previous tab = "<<std::endl;
    b1.switchToPrevTab();
    b1.closeCurrentTab();
    b1.display();
    std::cout<<"Switch to previous tab = "<<std::endl;
    b1.switchToPrevTab();
    b1.closeCurrentTab();
    b1.display();
    b1.showBookmarkTab();
    std::cout<<"Total Memory Consumption = "<<b1.total_memory()<<"MB"<<std::endl;
    b1.deleteTab();
    b1.display();
    b1.addNewTab("https://docs.google.com/","Google Docs",102.34);
    b1.display();
    std::cout<<"Switch to previous tab = "<<std::endl;
    b1.switchToPrevTab();
    std::cout<<"Switch to previous tab = "<<std::endl;
    b1.switchToPrevTab();
    std::cout<<"Switch to previous tab = "<<std::endl;
    b1.switchToPrevTab();
    b1.bookmarkCurrent();
    b1.showBookmarkTab();
    b1.total_memory();
    b1.deleteTab();
    b1.display();*/
    return 0;
}