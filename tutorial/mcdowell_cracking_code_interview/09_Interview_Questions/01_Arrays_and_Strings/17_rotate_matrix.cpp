/* 1.7 Rotate Matrix: Given an image represented by an NxN matrix, where each
                      each pixel in the image is 4 bytes, write a method to
                      rotate the image by 90 degrees. Can you do this in place?
*/

#include <iostream>
#include <algorithm>

using namespace std;

void rotate(int mat[][3])
{
    int temp[3][3];
    for (int n = 0; n < 3; ++n)
        for (int m = 0; m < 3; ++m)
            temp[m][3 - n - 1] = mat[n][m];

    for (int i=0; i < 3; ++i)
        for (int j = 0; j<3; ++j)
            mat[i][j] = temp[i][j];
}

int main()
{
    int mat[][3] = {{0,1,2},{3,4,5},{6,7,8}};

    // print top line
    for (int i = 0; i < 3; ++i)
        cout << mat[0][i] << " ";

    rotate(mat);

    // print right column
    cout << endl;
    for (int i = 0; i < 3; ++i)
        cout << mat[i][2] << " ";
    cout << endl;

    return 0;
}
