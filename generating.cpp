#include "Generating.h"

Generating::Generating(int **adress, int mazeHeight, int mazeWidth, int difficulty){
    mazeArray = adress;
    this->mazeHeight = mazeHeight;
    this->mazeWidth = mazeWidth;

    tempDiff(difficulty);

    reserveBordersMemory();
    reserveBoolMemory(this->mazeHeight, this->mazeWidth);

    srand(time(0));
}

Generating::~Generating()
{
    clearBordersMemory();
    clearBoolMemory(mazeHeight);
}

int Generating::generateMaze(int &startingRow, int &endingRow)
{
    Point currentPos;
    startingRow = rand() % mazeHeight;
    currentPos.row = startingRow;
    currentPos.col = 0;

    bool a = 0;
    int counter;

    do{
        counter = 0;
        resetbordersArray();
        resetvisitedArray();
        makeStartingPath(currentPos, counter, a);
    } while (a);

    endingRow = currentPos.row;

    do
        makeRandomPath(currentPos, randomDirection(currentPos));
    while (findNextPoint(currentPos));

    *(bordersArray[endingRow][mazeWidth-1].E) = 0;

    rewriteArray();

    return endingRow;
}

void Generating::makeStartingPath(Point &currentPos, int &counter, bool &a){
    visitedArray[currentPos.row][currentPos.col] = 1;
    char direction;
    direction = randomDirection(currentPos);

    if (direction == 'X'){
        a = 1;
        return;
    }

    if (currentPos.col == mazeWidth-1 && counter >= minLength && counter <=maxLength){
        a = 0;
        return;
    }

    if (direction == 'N'){
        *(bordersArray[currentPos.row][currentPos.col].N) = 0;
        currentPos.row--;
    }
    if (direction == 'E'){
        *(bordersArray[currentPos.row][currentPos.col].E) = 0;
        currentPos.col++;
    }
    if (direction == 'S'){
        *(bordersArray[currentPos.row][currentPos.col].S) = 0;
        currentPos.row++;
    }
    if (direction == 'W'){
        *(bordersArray[currentPos.row][currentPos.col].W) = 0;
        currentPos.col--;
    }
    counter++;
    makeStartingPath(currentPos, counter, a);
    return;
}

void Generating::makeRandomPath(Point &currentPos, char direction){
    visitedArray[currentPos.row][currentPos.col] = 1;

    if (direction == 'X')
        return;
    if (direction == 'N'){
        *(bordersArray[currentPos.row][currentPos.col].N) = 0;
        currentPos.row--;
    }
    if (direction == 'E'){
        *(bordersArray[currentPos.row][currentPos.col].E) = 0;
        currentPos.col++;
    }
    if (direction == 'S'){
        *(bordersArray[currentPos.row][currentPos.col].S) = 0;
        currentPos.row++;
    }
    if (direction == 'W'){
        *(bordersArray[currentPos.row][currentPos.col].W) = 0;
        currentPos.col--;
    }
    makeRandomPath(currentPos, randomDirection(currentPos));
    return;
}

char Generating::randomDirection(Point currentPos){
    bool dirN = 0,
            dirE = 0,
            dirS = 0,
            dirW = 0;
    int numberOfDirections = 0,
            i = 0;
    char *directionsArray,
            direction;

    if (currentPos.row-1 >= 0            && !(visitedArray[currentPos.row-1][currentPos.col])) {
        dirN = 1; numberOfDirections++;
    }
    if (currentPos.col+1 <= mazeWidth-1  && !(visitedArray[currentPos.row][currentPos.col+1])) {
        dirE = 1; numberOfDirections++;
    }
    if (currentPos.row+1 <= mazeHeight-1 && !(visitedArray[currentPos.row+1][currentPos.col])) {
        dirS = 1; numberOfDirections++;
    }
    if (currentPos.col-1 >= 0            && !(visitedArray[currentPos.row][currentPos.col-1])) {
        dirW = 1; numberOfDirections++;
    }

    directionsArray = new char[numberOfDirections];

    if (dirN) {
        directionsArray[i] = 'N'; ++i;
    }
    if (dirE) {
        directionsArray[i] = 'E'; ++i;
    }
    if (dirS) {
        directionsArray[i] = 'S'; ++i;
    }
    if (dirW) {
        directionsArray[i] = 'W'; ++i;
    }

    if (numberOfDirections == 0)
        return 'X';

    i = rand() % numberOfDirections;

    direction = directionsArray[i];

    delete[] directionsArray;

    return direction;
}

bool Generating::findNextPoint(Point &currentPos){
    for (int i=0; i<mazeHeight; ++i){
        for (int j=0; j<mazeWidth; j++) if (!visitedArray[i][j]){
            bool isPointFound = 0;
            if (j < mazeWidth-1  && visitedArray[i][j+1]){
                *(bordersArray[i][j].E) = 0;
                isPointFound = 1;
            }
            else if (i < mazeHeight-1 && visitedArray[i+1][j]){
                *(bordersArray[i][j].S) = 0;
                isPointFound = 1;
            }
            else if (j > 0            && visitedArray[i][j-1]){
                *(bordersArray[i][j].W) = 0;
                isPointFound = 1;
            }
            else if (i > 0            && visitedArray[i-1][j]){
                *(bordersArray[i][j].N) = 0;
                isPointFound = 1;
            }

            if (isPointFound){
                currentPos.row = i;
                currentPos.col = j;
                return 1;
            }
        }
    }
    return 0;
}

void Generating::tempDiff(int difficulty){
    if(difficulty == 0){
        minLength = 0;
        maxLength = RAND_MAX;
        return;
    }
    minLength = (mazeHeight + mazeWidth) * difficulty;
    maxLength = (mazeHeight + mazeWidth) * difficulty * 1.5;
}

void Generating::resetvisitedArray(){
    for (int i=0; i<mazeHeight; ++i)
        for (int j=0; j<mazeWidth; j++)
            visitedArray[i][j] = 0;
}

void Generating::rewriteArray(){
    for (int i=0; i<mazeHeight; ++i){
        for (int j=0; j<mazeWidth; j++){
            mazeArray[i][j] = 0
                              + int(*(bordersArray[i][j].N)) * 1
                              + int(*(bordersArray[i][j].E)) * 2
                              + int(*(bordersArray[i][j].S)) * 4
                              + int(*(bordersArray[i][j].W)) * 8;
        }
    }
}

void Generating::reserveBordersMemory(){
    bordersArray = new Borders *[mazeHeight];

    for (int i=0; i<mazeHeight; ++i)
        bordersArray[i] = new Borders [mazeWidth];

    for (int i=0; i<mazeHeight; ++i)
        for (int j=0; j<mazeWidth; j++){
            bordersArray[i][j].E = new bool;
            bordersArray[i][j].S = new bool;
        }

    for (int i=0; i<mazeHeight; ++i)
        bordersArray[i][0].W = new bool;

    for (int j=0; j<mazeWidth; j++)
        bordersArray[0][j].N = new bool;


    for (int i=1; i<mazeHeight; ++i)
        for(int j=1; j<mazeWidth; j++){
            bordersArray[i][j].N = bordersArray[i-1][j].S;
            bordersArray[i][j].W = bordersArray[i][j-1].E;
        }

    for (int i=1; i<mazeHeight; ++i)
        bordersArray[i][0].N = bordersArray[i-1][0].S;

    for (int j=1; j<mazeWidth; j++)
        bordersArray[0][j].W = bordersArray[0][j-1].E;
}

void Generating::resetbordersArray(){
    for (int i=0; i<mazeHeight; ++i)
        for (int j=0; j<mazeWidth; j++){
            *(bordersArray[i][j].N) = 1;
            *(bordersArray[i][j].E) = 1;
            *(bordersArray[i][j].S) = 1;
            *(bordersArray[i][j].W) = 1;
        }
}

void Generating::clearBordersMemory(){
    for (int i=0; i<mazeHeight; ++i)
        for (int j=0; j<mazeWidth; j++){
            delete bordersArray[i][j].E;
            delete bordersArray[i][j].S;
        }

    for (int i=0; i<mazeHeight; ++i)
        delete bordersArray[i][0].W;

    for (int j=0; j<mazeWidth; j++)
        delete bordersArray[0][j].N;

    for (int i=0; i<mazeHeight; ++i)
        delete[] bordersArray[i];
    delete[] bordersArray;
}

void Generating::reserveBoolMemory(int w, int k){
    visitedArray = new bool *[w];
    for (int i=0; i<w; ++i)
        visitedArray[i] = new bool [k];
}

void Generating::clearBoolMemory(int w){
    for (int i=0; i<w; ++i)
        delete[] visitedArray[i];
    delete visitedArray;
}
