#include <iostream>
#include <ctime>

using namespace std;

struct Node{
    struct Node *next;
    int xpos, ypos;

    Node(int x, int y){
        this->xpos = x;
        this->ypos = y;
        next = NULL;
    }

    void printNode(){
        cout << xpos << "," << ypos << " -> ";
    }

};

struct linkedList{

    struct Node *head;
    int size;

    linkedList(){
        head = NULL;
        int size = 0;
    }
    void pushBack(int x, int y){
        Node *temp = new Node(x,y);
        if (head == NULL){
            head = temp;
        }
        else {
            Node *p;
            for(p=head ; p->next!=NULL ;p=p->next);
            p->next = temp;
        }
    }
    Node getHead(){
        return *head;
    }

    void printList(){
        Node *temp = head;
        while(temp->next != NULL){
            temp->printNode();
            temp = temp->next;
        }
        cout << temp->xpos << "," <<temp->ypos << endl;
    }
};

struct Player{
    Node *pos = NULL;
    linkedList *path;

    Player(){
        path = new linkedList();
    }

    void move(int roll){
        while(pos->next != NULL && roll > 0){
            pos = pos->next;
            roll--;
        }
    }

    void display(){
        cout << "Current position: " << pos->xpos << "," << pos->ypos << endl;
    }
    void boardDisplay(Player* player){

        char board[48] ={};
        

    }

    void generatePath(int positions[][2], int size){
        for(int i = 0; i < size; i++){
            path->pushBack(positions[i][0],positions[i][1]);
            pos= path->head;
        }
    }

    int getX(){return pos->xpos;}
    int getY(){return pos->ypos;}

    bool testMove(Player *o){
        if(o->getX() == this->getX() && o->getY() == this->getY()){
            return true;
        }
        else return false;
    }

    bool safeSpace(int spaces[12][2]){
        for(int i = 0; i < 12; i++){
            if(this->getX() == spaces[i][0] && this->getY() == spaces[i][1]){
                return true;
            }
        }
        return false;
    }


};


int main(){
    srand(time(NULL));

    Player *p1 = new Player();
    Player *p2 = new Player();
    Player *p3 = new Player();
    Player *p4 = new Player();
    int positions1[48][2] = {{6,3},{6,2},{6,1},{6,0},{5,0},{4,0},{3,0},
                             {2,0},{1,0},{0,0},{0,1},{0,2},{0,3},{0,4},
                             {0,5},{0,6},{1,6},{2,6},{3,6},{4,6},{5,6},
                             {6,6},{6,5},{5,5},{4,5},{3,5},{2,5},{1,5},
                             {1,4},{1,3},{1,2},{1,1},{2,1},{3,1},{4,1},
                             {5,1},{5,2},{5,3},{5,4},{4,4},{3,4},{2,4},
                             {2,3},{2,2},{3,2},{4,2},{4,3},{3,3}
    };

    int positions2[48][2] = {{3,0},{2,0},{1,0},{0,0},{0,1},{0,2},{0,3},
                             {0,4},{0,5},{0,6},{1,6},{2,6},{3,6},{4,6},
                             {5,6},{6,6},{6,5},{6,4},{6,3},{6,2},{6,1},
                             {6,0},{5,0},{5,1},{5,2},{5,3},{5,4},{5,5},
                             {4,5},{3,5},{2,5},{1,5},{1,4},{1,3},{1,2},
                             {1,1},{2,1},{3,1},{4,1},{4,2},{4,3},{4,4},
                             {3,4},{2,4},{2,3},{2,2},{3,2},{3,3}
    };
    int positions3[48][2]={
            {0,3},  {0,4},  {0,5}, {0,6},  {1,6},  {2,6},  {3,6},
            {4,6},  {5,6},  {6,6},  {6,5},  {6,4},  {6,3}, {6,2},
            {6,1},  {6,0},  {5,0},  {4,0},  {3,0},  {2,0},  {1,0},
            {0,0},  {0,1},  {1,1},  {2,1},  {3,1},  {4,1},  {5,1},
            {5,2}, {5,3},  {5,4}, {5,5},  {4,5},  {3,5},  {2,5},
            {1,5}, {1,4}, {1,3}, {1,2},  {2,2},  {3,2},  {4,2},
            {4,3}, {4,4},  {3,4},  {2,4},  {2,3},  {3,3}
    };

    int positions4[48][2]={
            {3,6},  {4,6},  {5,6}, {6,6},  {6,5},  {6,4},  {6,3},
            {6,2},  {6,1},  {6,0},  {5,0},  {4,0},  {3,0}, {2,0},
            {1,0},  {0,0},  {0,1},  {0,2},  {0,3},  {0,4},  {0,5},
            {0,6},  {1,6},  {1,5},  {1,4},  {1,3},  {1,2},  {1,1},
            {2,1}, {3,1},  {4,1}, {5,1},  {5,2},  {5,3},  {5,4},
            {5,5}, {4,5}, {3,5}, {2,5},  {2,4},  {2,3},  {2,2},
            {3,2}, {4,2},  {4,3},  {4,4},  {3,4},  {3,3}
    };

    int safe[12][2] = {{0,0},{0,3},{0,6},{1,1},{1,5},{3,0},{3,6},{5,1},{5,5},{6,0},{6,3},{6,6}};
    p1->generatePath(positions1, 48);
    p2->generatePath(positions2, 48);
    p3->generatePath(positions3, 48);
    p4->generatePath(positions4, 48);
    /*
    p1->path->printList();
    p2->path->printList();
    p4->path->printList();
    p1->display();
    p1->move(3);
    p1->display();
    */
    bool won = false;
    bool won2=false;
    bool won3=false;
    bool won4=false;
    int dice;
    while ((won != true)||(won2!=true)||(won3!=true)||(won4!=true)) {
        if (won!=true){
            string enter;
            cout << "\n Press any key to continue.";
            cin >> enter;
            dice = (rand()) % 4 + 1;
            cout << "Moving player 1 " << dice << " spaces" << endl;
            p1->move(dice);
            cout << "Player 1 ";
            p1->display();
            if (p1->pos->next == NULL) {
                won = true;
                cout << "Player 1 has won!" << endl;
            } else if (!p1->safeSpace(safe)) {
                if (p1->testMove(p2)) {
                    p2->pos = p2->path->head;
                    cout << "Player 1 knocked player 2 back to start" << endl;
                } else if (p1->testMove(p3)) {
                    p3->pos = p3->path->head;
                    cout << "Player 1 knocked player 3 back to start" << endl;
                } else if (p1->testMove(p4)) {
                    p4->pos = p4->path->head;
                    cout << "Player 1 knocked player 4 back to start" << endl;
                }
            }
        }
        if (won2!=true){
            string enter;

            cout << "\n Press any key to continue.";
            cin >> enter;
            dice = (rand()) % 4 + 1;
            cout << "Moving player 2 " << dice << " spaces" << endl;
            p2->move(dice);
            cout << "Player 2 ";
            p2->display();
            if (p2->pos->next == NULL) {
                won2 = true;
                cout << "Player 2 has won!" << endl;
            } else if (!p2->safeSpace(safe)) {
                if (p2->testMove(p1)) {
                    p1->pos = p1->path->head;
                    cout << "Player 2 knocked player 1 back to start" << endl;
                } else if (p2->testMove(p3)) {
                    p3->pos = p3->path->head;
                    cout << "Player 2 knocked player 3 back to start" << endl;
                } else if (p2->testMove(p4)) {
                    p4->pos = p4->path->head;
                    cout << "Player 2 knocked player 4 back to start" << endl;
                }
            }
        }
        if (won3!=true){
            string enter;

            cout << "\n Press any key to continue.";
            cin >> enter;
            dice = (rand()) % 4 + 1;
            cout << "Moving player 3 " << dice << " spaces" << endl;
            p3->move(dice);
            cout << "Player 3 ";
            p3->display();
            if (p3->pos->next == NULL) {
                won3 = true;
                cout << "Player 3 has won!" << endl;
            } else if (!p3->safeSpace(safe)) {
                if (p3->testMove(p1)) {
                    p1->pos = p1->path->head;
                    cout << "Player 3 knocked player 1 back to start" << endl;
                } else if (p3->testMove(p2)) {
                    p2->pos = p2->path->head;
                    cout << "Player 3 knocked player 2 back to start" << endl;
                } else if (p3->testMove(p4)) {
                    p4->pos = p4->path->head;
                    cout << "Player 3 knocked player 4 back to start" << endl;
                }
            }
        }
        if (won4!=true){
            string enter;
            cout<<"\n Press any key to continue.";
            cin >>enter;
            dice=(rand()) % 4 + 1;
            cout << "Moving player 4 " << dice << " spaces"<< endl;
            p4->move(dice);
            cout << "Player 4 ";
            p4->display();
            if(p4->pos->next == NULL){
                won4 = true;
                cout << "Player 4 has won!" << endl;
            } else if(!p4->safeSpace(safe)) {
                if (p4->testMove(p1)) {
                    p1->pos = p1->path->head;
                    cout << "Player 4 knocked player 1 back to start" << endl;
                } else if (p4->testMove(p2)) {
                    p2->pos = p2->path->head;
                    cout << "Player 4 knocked player 2 back to start" << endl;
                } else if (p3->testMove(p3)) {
                    p3->pos = p3->path->head;
                    cout << "Player 4 knocked player 3 back to start" << endl;
                }
            }
        }

    }
    if (won == true&&won2==true&&won3==true&&won4==true){
        cout<<"END OF GAME";
    }
}
