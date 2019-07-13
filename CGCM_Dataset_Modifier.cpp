/*
 * ZM CGCM Dataset Modifier 
 * Source Date : 22/06/2019
 * Last Update : 12/07/2019
 * Author      : Mohammed ZAGANE
 * Licence     : /
 */

#include <iostream> // cout, cin
#include <fstream> // ifstream, ofstream

/*
 * LOC Metrics :
   1 Empty_Lines
   2 Lines_Of_Comments
   3 Lines_Of_Program
   4 Physic_Lines
 * Halstead Metrics :
   5 n1_Number_Of_Distinct_Operators 
   6 n2_Number_Of_Distinct_Operands 
   7 n_Program_Vocabulary 
   8 N1_Total_Number_Of_Operators 
   9 N2_Total_Number_Of_Operands 
   10 N_Program_Length 
   11 B_Number_of_Delivered_Bugs_1 
   12 B_Number_of_Delivered_Bugs_2 
   13 D_Difficulty 
   14 E_Effort 
   15 T_Time_Required_To_Program 
   16 V_Volume 
   17 N_Calculated_Program_Length 

 * McCab Metrics
   18 McCab_Number 

 * IsVulnerable (class label) :
    no
    yes
 
 */

/*
 * This function extract loc metric () from the given 
 * line (instance)
 */
std::string getLoc(std::string Line)
{
    int Index1, Index2;
    std::string Modified_Line;

    Index1 =0;

    for (int i=0; i<Line.length(); i++)
    {
        if(Line[i]==',')
        {
            Index1 ++;
        }

        if(Index1 == 4) // 4 is the end of the last lc metric (see the metrics description at Top)
        {
            Index2 = i;
            break;
        }
    }

    Modified_Line = Line.substr(0,Index2);

    // adding the class label  -------------------------------------------------
    if(Line[Line.length()-1] == 'o') // if the last char is 'o' => class label is "no"
    {
        Modified_Line = Modified_Line + ",no"; // add "no" 
    }
    else if(Line[Line.length()-1] == 's') // 
    {
        Modified_Line = Modified_Line + ",yes";
    }
    // --------- end : adding the class label ----------------------------------

    return Modified_Line ;
}

std::string getHalstead(std::string Line)
{
    int Index0, Index1, Index2;
    std::string Modified_Line;

    Index1 =0;
    Index0 =0;
    Index2 =0;
    bool isIndex0_Set = false;

    for (int i=0; i<Line.length(); i++)
    {
        if(Line[i]==',')
        {
            Index1 ++;
        }

        if(Index1 == 4 && !isIndex0_Set) // (4 +1 ) is the begening of Halstead metrics (see the metrics description at Top)
        {
            Index0 = i+1;
            isIndex0_Set = true;
        }

        if(Index1 == 17) // 17 is the end of Halstead metrics (see the metrics description at Top)
        {
            Index2 = i;
            break;
        }
    }

    Modified_Line = Line.substr(Index0,Index2 - Index0);

    if(Line[Line.length()-1] == 'o')
    {
        Modified_Line = Modified_Line + ",no";
    }
    else if(Line[Line.length()-1] == 's')
    {
        Modified_Line = Modified_Line + ",yes";
    }

    return Modified_Line ;
}

std::string getMcCab(std::string Line)
{
    int Index0, Index1;
    std::string Modified_Line;

    Index1 =0;
    Index0 =0;

    for (int i=0; i<Line.length(); i++)
    {
        if(Line[i]==',')
        {
            Index1 ++;
        }

        if(Index1 == 17) // (17 +1 ) is the begening of McCab metrics (see the metrics description at Top)
        {
            Index0 = i+1;
            break;
        }

    }

    Modified_Line = Line.substr(Index0,Line.length()-1);

    return Modified_Line ;
}

std::string getAll_Except_Zero(std::string Line)
{
    int Index0, Index1;
    std::string Modified_Line;

    Index1 =0;
    Index0 =0;

    for (int i=0; i<Line.length(); i++)
    {
        if(Line[i]==',')
        {
            Index1 ++;
        }

        if(Index1 == 2) // (17 +1 ) is the begening of McCab metrics (see the metrics description at Top)
        {
            Index0 = i+1;
            break;
        }

    }

    Modified_Line = Line.substr(Index0,Line.length()-1);

    return Modified_Line ;
}

int main()
{

    //variables
    
    const char * Original_File_Name = "CGCM_Dataset\\Arithmetic_expression.syse.arff";// full path to the file to process
    std::ifstream Original_File(Original_File_Name);
    const char * Modified_File_Name1 = "CGCM_Dataset\\CGLOC.arff";// full path to the result file1 (LOC Metrics)
    std::ofstream Modified_File1(Modified_File_Name1);
    const char * Modified_File_Name2 = "CGCM_Dataset\\CGHalstead.arff";// full path to the result file2 (Halstead Metrics)
    std::ofstream Modified_File2(Modified_File_Name2);
    const char * Modified_File_Name3 = "CGCM_Dataset\\CGMcCAB.arff";// full path to the result file3 (McCab Metrics)
    std::ofstream Modified_File3(Modified_File_Name3);
        
    std::string Original_Line, Modified_Line1, Modified_Line2, Modified_Line3;
    const int Data_Start_At = 23;// Begining of the lines (data section)

    std::cout << "ZM Dataset Modifier version 1.12.07.2019" << std::endl;

    if (!Original_File.good())
    {
        std::cout<< "Unable to open the original file :(";
        return -1;
    }

    if (!Modified_File1.good())
    {
        std::cout<< "Unable to open the modified file1 :(";
        return -1;
    }

    if (!Modified_File2.good())
    {
        std::cout<< "Unable to open the modified file2 :(";
        return -1;
    }

    if (!Modified_File3.good())
    {
        std::cout<< "unable to open the modified file3 :(";
        return -1;
    }

    

    int Line_Index = 0;

    while (getline(Original_File, Original_Line))
    {
        if(Line_Index < Data_Start_At) // writing the arff header 
        {
            Modified_File1 << Original_Line << std::endl;
            Modified_File2 << Original_Line << std::endl;
            Modified_File3 << Original_Line << std::endl;
            goto Skip_Processing;
        }

        //std::cout<< Original_Line << std::endl; //debuging
        Modified_File1 << getLoc(Original_Line) << std::endl;//Original_Line.substr(0,4) << std::endl;
        Modified_File2 <<  getHalstead(Original_Line) << std::endl;
        Modified_File3 << getMcCab(Original_Line) << std::endl;
        

        Skip_Processing :
        Line_Index++;

    }

    Original_File.close();
    Modified_File1.close();
    Modified_File2.close();
    Modified_File3.close();
    
    std::cout<< "Processing succefuly terminated :)"<< std::endl;
    std::cout<< "IMPORTANT :"<< std::endl;
    std::cout<< "Please modify the generated arff files headers manualy.  ^^) "<< std::endl;

    return 0;
}


