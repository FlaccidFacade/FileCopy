// Copy a file by certain buffer size
// Note size must be evenly divisable by buffersize
#include <iostream>
#include <fstream>
#include <chrono>

using namespace std;


int copy(ifstream& input, ofstream& output, long bs, long s){
   
    //define buffer
    char* buffer = new char [bs];

    //check for proper buffer size
    if(s % bs != 0){
        cout << "ERROR Invalid Buffer Size: " << bs << endl;
        return 0;
    }
   
    //copy by the buffer size
    for(long i = 0; i < s; i = i + bs){
        //read into buffer
        input.read(buffer, bs);
        //write from buffer
        output.write(buffer, bs);
    }

    //deallocate buffer
    delete[] buffer;
   
    return 1;
}

int main()
{

    ifstream input;
    input.open("input.dat");
    //get the file size
    input.seekg(0,ifstream::end);
    long fileSize = input.tellg();

    //use boolean to see if result is valid
    bool valid = 0;

    //start at minimum buffer size and go to max
    long BUFFERSIZE = 0;
    for( BUFFERSIZE = 1; BUFFERSIZE <= fileSize; BUFFERSIZE++){
        //open file streams
        ofstream output;
        output.open("output.dat");
        ifstream input;
        input.open("input.dat");

        //Check for file open
        if(!output || !input){
            cout << "ERROR Openning File\n";
            return 1;
        }

        //start timing here to take into account allocation of memory
        auto beg = chrono::high_resolution_clock::now();

        //copy the file
        valid = copy(input, output, BUFFERSIZE, fileSize);

        //stop timing here to take into account deallocation of memory
        auto end = chrono::high_resolution_clock::now();

        //determine elapsed time
        auto duration = chrono::duration_cast<chrono::nanoseconds>(end-beg);

        //only display valid results
        if(valid){
            cout << "Copying a file size of: " << fileSize << " with buffer size: " << BUFFERSIZE << " took :" << duration.count() << " ns." << endl;
        }
    
        //close the file streams and delete buffer
        output.close();
        input.close();
    }
    return 0;
}

