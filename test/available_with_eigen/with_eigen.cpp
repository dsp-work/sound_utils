/*
 * main.cpp
 *
 *  Created on: 2021/07/22
 *      Author: matsu
 */
#include <Eigen/Dense>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using namespace Eigen;
using namespace std;

void test_intro1();
void test_intro2_1();
void test_intro2_2();


int main( int argc, char** argv )
{
    vector< string > args( argv, argv + argc );

    if ( args.at( 1 ) == string( "intro1" ) )
    {
        test_intro1();
    }
    else if ( args.at( 1 ) == string( "intro2_1" ) )
    {
        test_intro2_1();
    }
    else if ( args.at( 1 ) == string( "intro2_2" ) )
    {
        test_intro2_2();
    }
    else
    {
        fprintf( stderr, "Matching test is not exist.\n" );
        exit( -1 );
    }

    return 0;
}

void test_intro1()
{
    MatrixXd m( 2, 2 );
    m( 0, 0 ) = 3;
    m( 1, 0 ) = 2.5;
    m( 0, 1 ) = -1;
    m( 1, 1 ) = m( 1, 0 ) + m( 0, 1 );
    std::cout << m << std::endl;
}

void test_intro2_1()
{
    MatrixXd m = MatrixXd::Random( 3, 3 );
    m = ( m + MatrixXd::Constant( 3, 3, 1.2 ) ) * 50;
    cout << "m =" << endl
         << m << endl;
    VectorXd v( 3 );
    v << 1, 2, 3;
    cout << "m * v =" << endl
         << m * v << endl;
}

void test_intro2_2()
{
    Matrix3d m = Matrix3d::Random();
    m = ( m + Matrix3d::Constant( 1.2 ) ) * 50;
    cout << "m =" << endl
         << m << endl;
    Vector3d v( 1, 2, 3 );

    cout << "m * v =" << endl
         << m * v << endl;
}