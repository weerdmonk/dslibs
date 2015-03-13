
#include "golum.h"
#include <iostream>

using namespace std;

int main() {
    chatServer *pServer = new chatServer(8888);

    cout << "object created" << endl;

    pServer->Start();

    return 0;

}
