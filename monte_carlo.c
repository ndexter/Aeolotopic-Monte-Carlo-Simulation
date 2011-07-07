//#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <omp.h>
extern "C"
{
    #include <gsl/gsl_math.h>
    #include <gsl/gsl_vector.h>
    #include <gsl/gsl_matrix.h>
    #include <gsl/gsl_blas.h>
}
#define PI 3.14159265358979323846264338327950288419716939937510 
//int numSpheres = 512;                             // the number of spheres in Santos 
int numSpheres = 1000;                              // the number of spheres 
int binNum = 500;                                   // the number of bins
long double hardCore = 0.0556;                      // hard core diameter
long double hardCoreSquared = 0.0556*0.0556;        // the square of the hardcore diameter
long double potentialRange = 0.091;                 // the range of the potential
long double potentialRangeSquared = 0.091*0.091;    // the square of the potential
long double squareWellDepthBoltzmann[35];           // test for hard core sphere interactions
long double squarePatchDepthBoltzmann[35];           // test for hard core sphere interactions
long double potentialRangeMult[35];
long double alpha = 0.05;                           //
long double jumpsize = 0.05;                        // max size of the jumps away from original position in a monte carlo step
long numMoved = 0;                                  // number of successful monte carlo steps
int samples = 0;
int testSamples = 0;
int a = 0;
long totalneighbors = 0;
long totalwellneighbors = 0;
long totalpatchneighbors = 0;
long totalneighborsprev = 0;
long totalwellneighborsprev = 0;
long totalpatchneighborsprev = 0;
long double etabar = 0.0;
long double etabarwell = 0.0;
long double etabarpatch = 0.0;
int movenum;
FILE *neighborout;
int testing = 0;

/**
 * all the variables necessary to define a bin
 * count is the number of spheres inside the bin
 * volume is the volume of the bin
 * sradius is the inner radius of the spherical shell
 * eradius is the outer radius of the spherical shell
 * sradius2 is the inner radius of the shell squared
 * eradius2 is the outer radius of the spherical shell squared
 */
typedef struct {
    long count;
    long double volume, sradius, eradius;
    long double sradius2, eradius2;
    long double sum, sumofsquares;
    long double avg, merr;
} Bin;

/**
 * all the variables needed to define the position and orrientation of a sphere
 * x, y, z are the positions of the sphere and are from 0 to 1 in each coordinate
 * a, b, c are the euler angles of the sphere in radians
 */
typedef struct {
    long double x,y,z; //position
    long double a,b,c; //euler angle of sphere
    long mcount;
    long wellneighbors, currentwellneighbors;
    long patchneighbors, currentpatchneighbors;
    double wellneighborssq;
    double patchneighborssq;
    long ncount;
} Sphere;

/**
 * function prototypes
 */
long double productBoltzmann(Sphere *s, Sphere *test, long old, long double delta);
void countNeighbors(Sphere *s, Sphere *test, long old, long double delta);
void Init(Sphere *s, long num);
void InitBins(Bin *b, int num);
void oneMonteCarloStep(Sphere *s);
void radialDistribution(Sphere *s, Bin *bin, long num, long binNum, FILE *radialf);
void printavg(double percent, Bin *b);
void printPositionVTK(Sphere *s, int radnum, double percent);
int patchWork(Sphere *test, Sphere *si);
//void oneRadialDistribution(Sphere *s, long old, long binNum, FILE *rad);

/**
 * the main program which initializes the spheres positons and then runs the 
 * monte carlo symulation
 * At the moment it does not take any command line arguments
 */
int main(int argn, char* argv[]){
    int i;
    clock_t endclock, startclock;
    FILE *finish, *radialf, *etaout, *santos, *paramtxt;
    //start a clock to figure out how much time the program uses
    startclock = clock();
    //initialize the files for the final positions and radial distribution
    char tmp[100];
    memset(tmp, 0, 100);
    Sphere *spheres, *testSpheres;
    Bin *bins, *testBins;
    double percent, dR = 0.0, dPercent = 0.01;

    //Santos Values
//    potentialRangeMult[0] = 1.05;
//    potentialRangeMult[1] = 1.05;
//    potentialRangeMult[2] = 1.05;
//    potentialRangeMult[3] = 1.10;
//    potentialRangeMult[4] = 1.10;
//    potentialRangeMult[5] = 1.10;
//    potentialRangeMult[6] = 1.20;
//    potentialRangeMult[7] = 1.20;
//    potentialRangeMult[8] = 1.20;
//    potentialRangeMult[9] = 1.30;
//    potentialRangeMult[10] = 1.30;
//    potentialRangeMult[11] = 1.30;
//    potentialRangeMult[12] = 1.40;
//    potentialRangeMult[13] = 1.40;
//    potentialRangeMult[14] = 1.40;
//    potentialRangeMult[15] = 1.50;
//    potentialRangeMult[16] = 1.50;
//    potentialRangeMult[17] = 1.50;
//    potentialRangeMult[18] = 1.60;
//    potentialRangeMult[19] = 1.60;
//    potentialRangeMult[20] = 1.60;
//    potentialRangeMult[21] = 1.70;
//    potentialRangeMult[22] = 1.70;
//    potentialRangeMult[23] = 1.70;
//    potentialRangeMult[24] = 1.80;
//    potentialRangeMult[25] = 1.80;
//    potentialRangeMult[26] = 1.80;
//    potentialRangeMult[27] = 1.90;
//    potentialRangeMult[28] = 1.90;
//    potentialRangeMult[29] = 2.00;
//    potentialRangeMult[30] = 2.00;
    //Santos Values
//    squareWellDepthBoltzmann[0] = 1.0/0.50;
//    squareWellDepthBoltzmann[1] = 1.0/0.70;
//    squareWellDepthBoltzmann[2] = 1.0/1.00;
//    squareWellDepthBoltzmann[3] = 1.0/0.50;
//    squareWellDepthBoltzmann[4] = 1.0/0.70;
//    squareWellDepthBoltzmann[5] = 1.0/1.00;
//    squareWellDepthBoltzmann[6] = 1.0/0.70;
//    squareWellDepthBoltzmann[7] = 1.0/1.00;
//    squareWellDepthBoltzmann[8] = 1.0/1.50;
//    squareWellDepthBoltzmann[9] = 1.0/1.00;
//    squareWellDepthBoltzmann[10] = 1.0/1.50;
//    squareWellDepthBoltzmann[11] = 1.0/2.00;
//    squareWellDepthBoltzmann[12] = 1.0/1.00;
//    squareWellDepthBoltzmann[13] = 1.0/1.50;
//    squareWellDepthBoltzmann[14] = 1.0/2.00;
//    squareWellDepthBoltzmann[15] = 1.0/1.50;
//    squareWellDepthBoltzmann[16] = 1.0/2.00;
//    squareWellDepthBoltzmann[17] = 1.0/3.00;
//    squareWellDepthBoltzmann[18] = 1.0/1.50;
//    squareWellDepthBoltzmann[19] = 1.0/2.00;
//    squareWellDepthBoltzmann[20] = 1.0/3.00;
//    squareWellDepthBoltzmann[21] = 1.0/2.00;
//    squareWellDepthBoltzmann[22] = 1.0/3.00;
//    squareWellDepthBoltzmann[23] = 1.0/5.00;
//    squareWellDepthBoltzmann[24] = 1.0/2.00;
//    squareWellDepthBoltzmann[25] = 1.0/3.00;
//    squareWellDepthBoltzmann[26] = 1.0/5.00;
//    squareWellDepthBoltzmann[27] = 1.0/3.00;
//    squareWellDepthBoltzmann[28] = 1.0/5.00;
//    squareWellDepthBoltzmann[29] = 1.0/3.00;
//    squareWellDepthBoltzmann[30] = 1.0/5.00;
//    squareWellDepthBoltzmann[1] = 2.400;
//    squareWellDepthBoltzmann[2] = 2.500;
//    squareWellDepthBoltzmann[3] = 2.650;
//    squareWellDepthBoltzmann[4] = 2.700;
//    squareWellDepthBoltzmann[5] = 2.800;
//    squareWellDepthBoltzmann[6] = 3.000;
//    squareWellDepthBoltzmann[7] = 3.100;
//    squareWellDepthBoltzmann[0] = 3.33097681297;
//    squareWellDepthBoltzmann[1] = 2.650;
//    squareWellDepthBoltzmann[2] = 1.60555434234;
//    squareWellDepthBoltzmann[3] = 1.15542608076;

    //Standard values:
    potentialRangeMult[0] = 1.05;
    potentialRangeMult[1] = 1.15;
    potentialRangeMult[2] = 1.25;
    squareWellDepthBoltzmann[0] = 2.000;
    squareWellDepthBoltzmann[1] = 2.000;
    squareWellDepthBoltzmann[2] = 2.000;
    squarePatchDepthBoltzmann[0] = 7.950;
    double v_patch = 0.0, v_well = 0.0;
    printf("------------------------------------------\n");
    //for(a = 0; a < 1; a++) {
    for(a = 0; a < 3; a++) {
        printf("Beginning lambda = %1.2Lf epsilon = %1.3Lf\n", potentialRangeMult[a], squareWellDepthBoltzmann[a]);
        printf("------------------------------------------\n");
        fflush(stdout);

        //open file for neighbor density
        memset(tmp, 0, 100);
        sprintf(tmp, "l%1.2Lfe%1.3Lf", potentialRangeMult[a], squareWellDepthBoltzmann[a]);
        mkdir(tmp,S_IRWXU);
        memset(tmp, 0, 100);
        sprintf(tmp, "l%1.2Lfe%1.3Lf/eta", potentialRangeMult[a], squareWellDepthBoltzmann[a]);
        mkdir(tmp,S_IRWXU);
        memset(tmp, 0, 100);
        sprintf(tmp, "l%1.2Lfe%1.3Lf/eta/etal%1.2Lfe%1.3Lf.txt", potentialRangeMult[a], squareWellDepthBoltzmann[a], potentialRangeMult[a], squareWellDepthBoltzmann[a]);
        etaout = fopen(tmp,"w");
        memset(tmp, 0, 100);
        sprintf(tmp, "l%1.2Lfe%1.3Lf/santos.txt", potentialRangeMult[a], squareWellDepthBoltzmann[a]);
        santos = fopen(tmp,"w");
        if(etaout == NULL){
            fprintf(stderr, "could not open file eta.txt\n");
            exit(EXIT_FAILURE);
        }
        if(santos == NULL){
            fprintf(stderr, "could not open file santos.txt\n");
            exit(EXIT_FAILURE);
        }
        fprintf(etaout,"%f %f %f %f %f\n", 0.0, 0.0, 0.0, 0.0, 0.0);
        fflush(etaout);

        //dPercent = 0.01;                                          
        //for(percent = 0.15; percent < 0.26; percent+= dPercent){ 
        dPercent = 0.01;
        for(percent = 0.01; percent < 0.21; percent+= dPercent){
            if(percent >= 0.03) dPercent = 0.02;
            if(percent >= 0.05) dPercent = 0.05;
            if(percent >= 0.10) dPercent = 0.10;
            printf("Percent: %1.2f", percent);
            memset(tmp, 0, 100);
            sprintf(tmp, "l%1.2Lfe%1.3Lf/vol%1.2fp", potentialRangeMult[a], squareWellDepthBoltzmann[a], percent);
            mkdir(tmp,S_IRWXU);
            memset(tmp, 0, 100);
            sprintf(tmp, "l%1.2Lfe%1.3Lf/vol%1.2fp/final_pos.txt", potentialRangeMult[a], squareWellDepthBoltzmann[a], percent);
            finish = fopen(tmp, "w");
            if(finish == NULL){
                fprintf(stderr, "could not open file final_pos.txt\n");
                exit(EXIT_FAILURE);
            }
            memset(tmp, 0, 100);
            sprintf(tmp, "l%1.2Lfe%1.3Lf/vol%1.2fp/params.txt", potentialRangeMult[a], squareWellDepthBoltzmann[a], percent);
            paramtxt = fopen(tmp,"w");
            if(paramtxt == NULL){
                fprintf(stderr, "could not open file params.txt\n");
                exit(EXIT_FAILURE);
            }
            // Santos paper calc...
            //hardCore = cbrt(percent/((double)numSpheres));
            // Standard volume fraction calc...
            hardCore = cbrt(percent/((double)numSpheres*4.0/3.0*PI))*2.0;
            hardCoreSquared = pow(hardCore,2);
            potentialRange = potentialRangeMult[a]*hardCore;
            potentialRangeSquared = pow(potentialRange,2);
            dR = fabs((potentialRange-hardCore)/((double)50.0)); // size of spacing of bins
            binNum=ceil((0.5-hardCore)/dR);

            //Calculate necessary energy for patch/well balance
            //v_patch = 4.0/3.0*(30.0*PI/180.0)*(pow(potentialRangeMult[0]*hardCore/2.0,3.0)-pow(hardCore/2.0,3.0));
            //v_well = 4.0/3.0*((180.0-30.0)*PI/180.0)*(pow(potentialRangeMult[0]*hardCore/2.0,3.0)-pow(hardCore/2.0,3.0));
            //squarePatchDepthBoltzmann[a] = log(exp(squareWellDepthBoltzmann[a])*v_well/v_patch);

            //printf("\n%Lf * %f = %f * %f\n",squarePatchDepthBoltzmann[a],v_patch,exp(squareWellDepthBoltzmann[a]),v_well);

            fprintf(santos,"---------------------------------------------------------\n");
            fprintf(santos,"p g(1+) SEM g(l-) SEM g(l+) SEM \n", hardCore+dR, potentialRange-dR, potentialRange+dR);
            fprintf(santos,"p g(%Lf) SEM g(%Lf) SEM g(%Lf) SEM \n", hardCore+dR, potentialRange-dR, potentialRange+dR);
            //fprintf(santos,"---------------------------------------------------------\n");
            //alpha = cbrt(1.0/((double)numSpheres)/percent);
            //alpha = 1.715*hardCore;
            //alpha = 1.0;
            //alpha = (1.893904-5.391428*percent)*hardCore;
            jumpsize = alpha;
            printf("\tRadius of spheres: %3.10Lf\n", hardCore/2.0);
            memset(tmp, 0, 100);

            //verify in bounds...
            double vps = 4.0/3.0*PI*pow(hardCore/2.0,3);
            printf("Volume per sphere %f by %d spheres = %f\n", vps, numSpheres, vps*numSpheres);

            //define and array of spheres to use in the simulation
            spheres = (Sphere *)malloc(numSpheres*sizeof(Sphere));
            //define an array of bins to use for calculation
            bins = (Bin *)malloc(binNum*sizeof(Bin));
            //create a seed for the random number generator based on the time
            time_t seed = (unsigned)time(NULL);
            srand(seed);
            //initialize the sphere positions making sure none overlap
            Init(spheres, numSpheres);
            InitBins(bins, binNum);
            //initialize the total neighbors
            //totalneighbors = 0;
            //totalwellneighbors = 0;
            //totalpatchneighbors = 0;
            memset(tmp, 0, 100);
            sprintf(tmp, "l%1.2Lfe%1.3Lf/vol%1.2fp/neighbors.txt", potentialRangeMult[a], squareWellDepthBoltzmann[a], percent);
            neighborout = fopen(tmp,"w");
            //run the amount of steps needed for the simulation
            int radnum = 0;
            int avgmoves = 0;
            int mps = 0;
            int j;
            double testAlpha=0.0;
            double prevaccepted = 10.0, prevacceptedact = 0.0;
            int testMoves=100;
            testing = 1;
            for(testAlpha=0.01*hardCore;testAlpha<=1.0;testAlpha+=0.01*hardCore){
                //printf("Testing %3.10f jumpsize, %3.10Lf diameter\n", testAlpha, hardCore);
                //define an array of spheres to use in the simulation
                testSpheres = (Sphere *)malloc(numSpheres*sizeof(Sphere));
                //define an array of bins to use for calculation
                testBins = (Bin *)malloc(binNum*sizeof(Bin));
                //printf("Making test environment\n");
                memcpy(testSpheres, spheres, numSpheres*sizeof(Sphere)); 
                memcpy(testBins, bins, binNum*sizeof(Bin)); 
                //if(testSpheres[1].x == spheres[1].x) printf("spheres look good\n");
                //else printf("nope: test = %3.5f, actual = %3.5f\n", testSpheres[1].x, spheres[1].x);
                //if(testBins[1].volume == bins[1].volume) printf("bins look good\n");
                //else printf("nope: test = %3.5f, actual = %3.5f\n", testBins[1].volume, bins[1].volume);
                jumpsize = testAlpha;
                for(i=0;i<=testMoves;i++){
                    oneMonteCarloStep(testSpheres);
                    /*for(j = 0; j < numSpheres; j++) {
                        mps += testSpheres[j].mcount;
                    }
                    mps = mps/numSpheres;
                    if( mps > avgmoves ) {
                        //if(testSamples % 10 == 0 && testSamples != 0){
                        //    printf("%d\n", i);
                        //    fflush(stdout);
                        //} else {
                        //    printf("%d, ", i);
                        //    fflush(stdout);
                        //}
                        radialDistribution(testSpheres, testBins, numSpheres, binNum, radialf);
                        testSamples++;
                        avgmoves += 3;
                    }
                    mps = 0;*/
                }
                if(fabs(0.5-((double)numMoved)/((double)testMoves)) < prevaccepted){
                    prevaccepted = fabs(0.5-((double)numMoved)/((double)testMoves));
                    prevacceptedact = ((double)numMoved)/((double)testMoves);
                    //printf("found: %3.5f=%ld/%d ",prevacceptedact,numMoved,testMoves);
                    alpha = testAlpha;
                }
                free(testSpheres);
                free(testBins);
                numMoved = 0;
            }
            testing = 0;
            jumpsize = alpha;
            printf("best jump size found: %3.5Lf, associated acceptance rate: %1.1f\n", jumpsize, prevacceptedact);
            radnum = 0;
            mps = 0;
            avgmoves = 0;

            int numMoves=100000000;
            fprintf(paramtxt,"lambda = %Lf \n", potentialRangeMult[a]);
            fprintf(paramtxt,"epsilon = %Lf \n", squareWellDepthBoltzmann[a]);
            fprintf(paramtxt,"number of moves = %d \n", numMoves);
            fprintf(paramtxt,"num spheres = %d \n", numSpheres);
            fprintf(paramtxt,"radius of spheres = %3.10Lf \n", hardCore/2.0);
            fprintf(paramtxt,"range of potential = %3.10Lf \n", potentialRange);
            fprintf(paramtxt,"volume per sphere = %f \n", vps);
            fprintf(paramtxt,"volume fraction = %f \n", percent);
            fprintf(paramtxt,"vps * num spheres = %f \n", vps*numSpheres);
            fprintf(paramtxt,"dR of shells = %f \n", dR);
            fprintf(paramtxt,"number of bins = %d \n", binNum);
            fprintf(paramtxt,"jumpsize = %Lf \n", jumpsize);
            fprintf(paramtxt,"seed for rand = %d", (int)seed);
            fflush(paramtxt);
            fclose(paramtxt);

            int lastsamplemovenum = 0;
            double dmoves = 0.0;
            //int numMoves=100000;
            for(movenum=0;movenum<=numMoves;movenum++){
                oneMonteCarloStep(spheres);
                for(j = 0; j < numSpheres; j++) {
                    mps += spheres[j].mcount;
                }
                mps = mps/numSpheres;
                if( mps > avgmoves ) {
                    if(samples % 10 == 0 && samples != 0){
                        printf("%d \t\tdmoves = %10.1f\n", movenum, dmoves/10.0);
                        fflush(stdout);
                        dmoves = 0.0;
                    } else {
                        printf("%d, ", movenum);
                        fflush(stdout);
                        fflush(neighborout);
                        dmoves += movenum - lastsamplemovenum;
                        lastsamplemovenum = movenum;
                    }
                    memset(tmp, 0, 100);
                    sprintf(tmp, "l%1.2Lfe%1.3Lf/vol%1.2fp", potentialRangeMult[a], squareWellDepthBoltzmann[a], percent);
                    mkdir(tmp,S_IRWXU);
                    memset(tmp, 0, 100);
                    sprintf(tmp, "l%1.2Lfe%1.3Lf/vol%1.2fp/radial", potentialRangeMult[a], squareWellDepthBoltzmann[a], percent);
                    mkdir(tmp,S_IRWXU);
                    memset(tmp, 0, 100);
                    sprintf(tmp, "l%1.2Lfe%1.3Lf/vol%1.2fp/radial/%d.txt", potentialRangeMult[a], squareWellDepthBoltzmann[a], percent, radnum);
                    printPositionVTK(spheres, radnum, percent);
                    //radialf = fopen(tmp,"w");
                    //if(radialf == NULL){
                    //    fprintf(stderr, "could not open file %d.txt\n", radnum);
                    //    exit(EXIT_FAILURE);
                    //}
                    radnum++;
                    radialDistribution(spheres, bins, numSpheres, binNum, radialf);
                    samples++;
                    //fflush(radialf);
                    //fclose(radialf);
                    avgmoves += 3;
                    memset(tmp, 0, 100);
                }
                mps = 0;
            }
            //record the final positions
            printf("\nNumber moved %ld", numMoved);
            printf("\tPercent moved %9.2f", ((double)numMoved)/((double)numMoves));
            numMoved = 0;
            double etaavg = 0.0;
            double etaavgwell = 0.0;
            double etaavgpatch = 0.0;
            double meanerror = 0.0;
            double meanerrorwell = 0.0;
            double meanerrorpatch = 0.0;
            double asymptote = 0.0;
            long sumncount = 0;
            for(i=0; i<numSpheres; i++){
                fprintf(finish,"%Lf %Lf %Lf %Lf %Lf %Lf\n",spheres[i].x,spheres[i].y,spheres[i].z,spheres[i].a,spheres[i].b,spheres[i].c);
                etaavg+=((double)spheres[i].wellneighbors + (double)spheres[i].patchneighbors)/((double)spheres[i].ncount);
                etaavgwell+=((double)spheres[i].wellneighbors)/((double)spheres[i].ncount);
                etaavgpatch+=((double)spheres[i].wellneighbors)/((double)spheres[i].ncount);
                sumncount+=spheres[i].ncount;
            }
            etaavg=etaavg/((double)numSpheres);
            etaavgwell=etaavgwell/((double)numSpheres);
            etaavgpatch=etaavgpatch/((double)numSpheres);
            for(i=0; i<numSpheres; i++){
                meanerror+=pow(((double)spheres[i].wellneighbors + (double)spheres[i].patchneighbors)/((double)spheres[i].ncount)-etaavg,2.0);
                meanerrorwell+=pow(((double)spheres[i].wellneighbors)/((double)spheres[i].ncount)-etaavgwell,2.0);
                meanerrorpatch+=pow(((double)spheres[i].patchneighbors)/((double)spheres[i].ncount)-etaavgpatch,2.0);
            }
            meanerror=sqrt(meanerror/((double)numSpheres-1.0))/sqrt((double)numSpheres);
            meanerrorwell=sqrt(meanerrorwell/((double)numSpheres-1.0))/sqrt((double)numSpheres);
            meanerrorpatch=sqrt(meanerrorpatch/((double)numSpheres-1.0))/sqrt((double)numSpheres);
            // meanerror = sqrt((spheres[i].wellneighborssq-pow(etaavg,2.0)*((double)sumncount))/((double)sumncount-1.0))/sqrt((double)sumncount);
            asymptote = 4.0*PI*((double)numSpheres)*exp(squareWellDepthBoltzmann[a])/3.0*pow(potentialRangeMult[a]*hardCore,3.0)-
                4.0*PI*((double)numSpheres)*exp(squareWellDepthBoltzmann[a])/3.0*pow(hardCore,3.0);
            fprintf(etaout,"%f %f %f %f %f %f %f %f %f %f %f\n",percent, etaavg, etaavg-meanerror, etaavg+meanerror, 
                                                       etaavgwell, etaavgwell-meanerrorwell, etaavgwell+meanerrorwell, 
                                                       etaavgpatch, etaavgpatch-meanerrorpatch, etaavgpatch+meanerrorpatch, asymptote);
            //fprintf(etaout,"%f %f %f\n",percent, etaavg, asymptote);
            fflush(etaout);
            //find the radial distribution of the spheres 
            //radialDistribution(spheres, bins, numSpheres, 100, radialf);
            printf("\t\tNumber of samples %d\n", samples);
            printavg(percent, bins);
            fprintf(santos,"%f %Lf %Lf %Lf %Lf %Lf %Lf\n\n",percent, bins[0].avg, bins[0].merr, bins[49].avg, bins[49].merr, bins[50].avg, bins[50].merr);
            fflush(santos);
            endclock = clock ();
            //record the time taken to run the simulation
            printf("time taken %9.2f seconds\n",
                    (float)(endclock-startclock)/(float)CLOCKS_PER_SEC );
            free(spheres);
            free(bins);
            fclose(finish);
            printf("------------------------------------------\n");
        }
        fflush(etaout);
        fclose(etaout);
        fflush(santos);
        fclose(santos);
        fflush(neighborout);
        fclose(neighborout);
    }
    return 0;
}

void printavg(double percent, Bin *bins) {
    FILE *average;
    char tmp2[100];
    long double mean=0.0, meanp=0.0, meanerror=0.0;
    memset(tmp2, 0, 100);
    sprintf(tmp2, "l%1.2Lfe%1.3Lf/vol%1.2fp/radial/avg.txt", potentialRangeMult[a], squareWellDepthBoltzmann[a], percent);
    average = fopen(tmp2, "w");
    if(average == NULL){
        fprintf(stderr, "could not open file avg.txt\n");
        exit(EXIT_FAILURE);
    }
    int j;
    long double area = 0.0;
    for(j = 0; j < binNum; j++ ) {
        mean = bins[j].sum/((double)samples);
        bins[j].avg = mean;
        if(j!=0) area += 4.0*PI*numSpheres*(bins[j].eradius-bins[j].sradius)*(pow(bins[j].eradius,2.0)*mean+pow(bins[j].sradius,2.0)*meanp)/2.0; 
        //variance = bins[j].sumofsquares/((double)samples-1.0)-((double)samples)/((double)samples-1.0)*pow(mean,2.0);
        meanerror = sqrt((bins[j].sumofsquares-pow(bins[j].sum,2.0)/((double)samples))/((double)samples-1.0))/sqrt((double)samples);
        bins[j].merr = meanerror;
        fprintf(average,"%Lf %Lf %Lf %Lf %Lf\n ", bins[j].sradius/hardCore, mean, mean-meanerror, mean+meanerror, area);
        meanp = mean;
    }
    fflush(average);
    fclose(average);
    samples = 0;
    testSamples = 0;
    etabar = ((double)totalneighbors)/((double)numSpheres);
    etabarwell = ((double)totalwellneighbors)/((double)numSpheres);
    etabarpatch = ((double)totalpatchneighbors)/((double)numSpheres);
    printf("after simulation neighbor count: %ld\n",totalneighbors);
    printf("after simulation well neighbor count: %ld\n",totalwellneighbors);
    printf("after simulation patch neighbor count: %ld\n",totalpatchneighbors);
    if(!testing){
        fprintf(neighborout,"%d %ld %ld %ld\n ", movenum, totalneighbors, totalwellneighbors, totalpatchneighbors);
    }
    fflush(neighborout);
}

void printPositionVTK(Sphere *s, int radnum, double percent) {
    char tmp2[100];
    FILE *vtkpos;
    memset(tmp2, 0, 100);
    sprintf(tmp2, "l%1.2Lfe%1.3Lf/vol%1.2fp/radial/%d.vtk", potentialRangeMult[a], squareWellDepthBoltzmann[a], percent, radnum);
    vtkpos = fopen(tmp2, "w");
    fprintf(vtkpos, "# vtk DataFile Version 2.0\n");
    fprintf(vtkpos, "3D Proteins\n");
    fprintf(vtkpos, "ASCII\n");
    fprintf(vtkpos, "DATASET UNSTRUCTURED_GRID \n");
    fprintf(vtkpos, "POINTS %d float\n", numSpheres);
    int i = 0;
    for(i = 0; i < numSpheres; i++){
        fprintf(vtkpos, "%Lf %Lf %Lf\n", s[i].x, s[i].y, s[i].z);
    }
    fprintf(vtkpos, "CELLS %d %d\n", numSpheres, numSpheres*2);
    for(i = numSpheres-1; i > -1; i--){
        fprintf(vtkpos, "1 %d\n",i);
    }
    fprintf(vtkpos, "CELL_TYPES %d\n", numSpheres);
    for(i = 0; i < numSpheres; i++){
        if(i % 10 == 0) {
            fprintf(vtkpos, "1\n");
        } else {
            fprintf(vtkpos, "1 ");
        }
    }
    fprintf(vtkpos, "POINT_DATA %d\n", numSpheres);
    fprintf(vtkpos, "SCALARS scalars float 1\n");
    fprintf(vtkpos, "LOOKUP_TABLE default\n");
    for(i = 1; i <= numSpheres; i++){
        if(i % 10 == 0) {
            fprintf(vtkpos, "%d\n", i);
        } else {
            fprintf(vtkpos, "%d ", i);
        }
    }
    fflush(vtkpos);
    fclose(vtkpos);
}

void InitBins(Bin *bins, int binNum) {
    long double deltaX = 0.0, deltaY = 0.0, deltaZ = 0.0;
    long double radius2 = 0.0, dR = 0.0, radius = 0.0;
    long double idealDens = 0.0;
    long double ratio = 0.0;
    long i = 0, n = 0, j = 0, index = 0;
    // dR = 0.5/((double)binNum);
    // dR = (0.5-hardCore)/((double)binNum); // size of spacing of bins
    dR = fabs((potentialRange-hardCore)/((double)50.0)); // size of spacing of bins
    binNum=ceil((0.5-hardCore)/dR);
    //initialize the bins
    //find the volume and starting and stopping radius
    for(j=0;j<binNum;j++){
        bins[j].count = 0; //make sure the starting count is 0
		// bins[j].sradius = j * dR;
		// bins[j].eradius = (j+1)*dR;
        bins[j].sradius = j * dR + hardCore;
        bins[j].eradius = (j + 1) * dR + hardCore;
        bins[j].sradius2 = bins[j].sradius
            * bins[j].sradius;
        bins[j].eradius2 = bins[j].eradius
            * bins[j].eradius;
        bins[j].volume = 4.0/3.0 * PI 
            * (pow(bins[j].eradius,3.0)-pow(bins[j].sradius,3.0));
        bins[j].sum = 0.0;
        bins[j].sumofsquares = 0.0;
        bins[j].avg = 0.0;
        bins[j].merr = 0.0;
    }
}

/**
 * Given an array of spheres 
 * create a random positions for the spheres and make sure that
 * the spheres do not overlap
 */
void Init(Sphere *s, long num){
    // The x, y, and z distances between this sphere and any other
    long double deltaX, deltaY, deltaZ;
    // the radial separation between spheres, squared
    long double radius2;
    // continue placing spheres while this is 1, if it is 0 then 
    // 2 spheres are inside one another.
    int goOn = 1;
    long i,n;
    // Stamp the beginning of the positioning process, when 
    // vol. frac. is high, this can take a long time.
    printf("Positioning:");
    fflush(stdout);
    for(i=0;i<num;i++){
        // Stamp the 10, 20, 30,.... percent completion times so we know
        // how much of the process has been completed.
        if(i % (num/10) == 0){
            printf("%ld-->",i);
            fflush(stdout);
        }
        //keep on picking positions until no overlap
        do{    
            // generate random positions in the unit cube
            s[i].x=(long double)rand()/((long double)RAND_MAX);
            s[i].y=(long double)rand()/((long double)RAND_MAX);
            s[i].z=(long double)rand()/((long double)RAND_MAX);
            // check to make sure no overlap
            goOn=1;
            // for each of the other spheres,
            for(n=0;n<i;n++){
                // check the distances
                deltaX=fabs(s[i].x-s[n].x);
                if(deltaX>.5) deltaX = 1.0-deltaX;
                deltaY=fabs(s[i].y-s[n].y);
                if(deltaY>.5) deltaY = 1.0-deltaY;
                deltaZ=fabs(s[i].z-s[n].z);
                if(deltaZ>.5) deltaZ = 1.0-deltaZ;
                // combining the squared x, y, z separations
                radius2 = deltaX*deltaX
                    +deltaY*deltaY+deltaZ*deltaZ;
                // and testing to see if the distances are 
                // less than the diameter squared
                if(radius2<hardCoreSquared) goOn = 0;
            }
        }while(goOn==0);
        //pick random angles, see the ZXZ' Euler angles 
        //rotation scheme for details

        // a is azimuthal rotation
        s[i].a=2.0*PI*(long double)rand()/((long double)RAND_MAX);
        // b is polar rotation
        s[i].b=acos(1.0-2.0*(((long double)rand())/((long double)RAND_MAX)));
        // c is the 2nd azimuthal rotation 
        s[i].c=2.0*PI*(long double)rand()/((long double)RAND_MAX);

        // initializee the various statistic keeping parameters:
        // the number of moves.
        s[i].mcount = 0;
        // the current number of neighbors in the well
        s[i].currentwellneighbors = 0;
        // the current number of patch neighbors
        s[i].currentpatchneighbors = 0;

        // the following parameters are used to reduce computation time,
        // instead of recounting the number of neighbors at each step,
        // they are updated whenever a move is accepted,
        // and contribute to the total number of neighbors,
        // which is correspondingly updated move-wise, 
        // instead of being retotalled after every move.

        // the per-sphere total number of neighbors that have ever been in the well 
        s[i].wellneighbors = 0;
        // the per-sphere square of the total number of well neighbors
        s[i].wellneighborssq = 0.0;
        // the per-sphere total number of patch neighbors that have ever been in the patch
        s[i].patchneighbors = 0;
        // the per-sphere square of the total number of patch neighbors
        s[i].patchneighborssq = 0.0;
        // the number of times these total sum neighbor numbers have been counted
        s[i].ncount = 0;
    }
    // After all spheres have been placed, initialize the total number of neighbors to 0
    totalneighbors = 0;
    // same for the total well neighbors
    totalwellneighbors = 0;
    // same for the total patch neighbors
    totalpatchneighbors = 0;
    // Stamp completion
    printf("Done!\n");
    fflush(stdout);
    // Count all of the neighbors of the system, Order(1/2n^3) computation
    for(i=0;i<num;i++){
        // count the neighbors
        countNeighbors(s, &s[i], i, potentialRange);
        // sum the counts of current and patch neighbors after this sphere
        // has had its current neighbor quantity counted
        totalneighbors += s[i].currentwellneighbors + s[i].currentpatchneighbors;
        // similarly for the total well neighbors
        totalwellneighbors += s[i].currentwellneighbors;
        // and the total patch neighbors
        totalpatchneighbors += s[i].currentpatchneighbors;
        // If the total neighbors is ever less than 0, something is wrong...
        if(totalneighbors < 0){
            // jalapeno is Nick's debugging point...
            // I set a breakpoint at jalapeno=0, a useless statement
            // to observe the properties that led to such a count...
            int jalapeno = 0;
        }
    }
    // calculate the average number of neighbors
    etabar = ((double)totalneighbors)/((double)num);
    // and the average in the well
    etabarwell = ((double)totalwellneighbors)/((double)num);
    // and the average in the patch
    etabarpatch = ((double)totalpatchneighbors)/((double)num);
    // Let the user know the initial count for this parameterization
    printf("finished counting neighbors: %ld\n", totalneighbors);
    printf("finished counting well neighbors: %ld\n", totalwellneighbors);
    printf("finished counting patch neighbors: %ld\n", totalpatchneighbors);
    fflush(stdout);
}

/**
 * calculate the radial distribution of a group of spheres and
 * write the distribution to a file
 *
 * s is an array of spheres
 * num is the number of spheres in the array
 * binNum is the number of bins to calculate
 * radialf is a file to write the distribution to
 *
 */
void radialDistribution(Sphere *s, Bin *bins, long num, long binNum, FILE *radialf){
    long double deltaX = 0.0, deltaY = 0.0, deltaZ = 0.0;
    long double radius2 = 0.0, dR = 0.0, radius = 0.0;
    long double idealDens = 0.0;
    long double ratio = 0.0, numExpected = 0.0;
    long countLarge = 0; // number of distances between spheres greater than .5
    long countSmall = 0;
    long i = 0, n = 0, j = 0, index = 0;
    idealDens = (long double) num; // the number density
    // dR = 0.5/((double)binNum);
    // dR = (0.5-hardCore)/((double)binNum); // size of spacing of bins
    dR = fabs((potentialRange-hardCore)/((double)50.0)); // size of spacing of bins
    //calculate the shortest distance between all spheres
    //choose a sphere
    for(i = 0; i < num; i++){
        //choose another sphere making sure not to choose pairs that the distance
        //has already been calculated for
        for(n = i + 1; n < num; n++){
            radius2 = 0.0;
            radius = 0.0;
            if(i!=n){
                //calculate shortest radius by accounting for periodic boundary
                deltaX=fabs(s[i].x-s[n].x);
                if(deltaX>0.5) deltaX = 1.0-deltaX;
                deltaY=fabs(s[i].y-s[n].y);
                if(deltaY>0.5) deltaY = 1.0-deltaY;
                deltaZ=fabs(s[i].z-s[n].z);
                if(deltaZ>0.5) deltaZ = 1.0-deltaZ;
                radius2 = deltaX*deltaX
                    +deltaY*deltaY+deltaZ*deltaZ;
                // Determine correct binning
                if(radius2>0.25){
                    //larger than half of the container size
                    countLarge++;
                }else{
                    //find the index of the correct bin and add to bin
                    radius = sqrt(radius2);
                    // index = (long)floor(radius/dR);
                    index = (long)floor((radius-hardCore)/dR);
                    bins[index].count++;
                    countSmall++;
                }
            }
        }
    }
    //fprintf(radialf,"#greater than .5 %ld\n", countLarge);
    //fprintf(radialf,"#less than .5 %ld\n", countSmall);
    long totalCounted = 0;
    for(j=0;j<binNum;j++){
        // calculate the number of expected centers in bin
        numExpected = idealDens*bins[j].volume;
        // normalize and calculate ratio of centers in bin to expected centers
        ratio = (2.0/((long double)num))*(((long double)bins[j].count)/numExpected);
        totalCounted += bins[j].count;
        bins[j].count = 0;
        //record to file
        bins[j].sum += ratio;
        bins[j].sumofsquares += pow(ratio,2.0);
        //if(radialf != 0) 
        //fprintf(radialf,"%Lf %Lf\n ", bins[j].sradius/hardCore, ratio);
    }
    //fprintf(radialf,"#counted in all bins this round %ld", totalCounted);
}

/**
 * one Monte Carlo step
 * takes an array of sphere positons
 */
void oneMonteCarloStep(Sphere *s){
    long pos;
    // tempnew is a candidate for a move
    Sphere tempnew;
    long double oldBoltzmann = 0.0, newBoltzmann = 0.0, random;
    int oldneighbors = 0;
    int oldwellneighbors = 0;
    int oldpatchneighbors = 0;
    //pick a random sphere
    pos = rand()%numSpheres;

    oldBoltzmann = productBoltzmann(s, &s[pos], pos, potentialRange);

    oldneighbors = (s[pos].currentwellneighbors + s[pos].currentpatchneighbors);
    oldwellneighbors = s[pos].currentwellneighbors;
    oldpatchneighbors = s[pos].currentpatchneighbors;
    /*
    oldneighbors = s[pos].currentwellneighbors + s[pos].currentpatchneighbors;
    oldwellneighbors = s[pos].currentwellneighbors;
    oldpatchneighbors = s[pos].currentpatchneighbors;
    */
    etabar = ((double)totalneighbors)/((double)numSpheres);
    etabarwell = ((double)totalwellneighbors)/((double)numSpheres);
    etabarpatch = ((double)totalpatchneighbors)/((double)numSpheres);
    //if(!testing && abs(totalneighborsprev - totalneighbors) > 20){
    /*if(!testing && (movenum % 1000 == 0)){
        fprintf(neighborout,"%d %ld %ld %ld\n ", movenum, totalneighbors, totalwellneighbors, totalpatchneighbors);
        totalneighborsprev = totalneighbors;
        totalwellneighborsprev = totalwellneighbors;
        totalpatchneighborsprev = totalpatchneighbors;
    }*/
    //pick a new position for the sphere
    tempnew.x = jumpsize*((long double)rand()/((long double)RAND_MAX)-0.5)+s[pos].x;
    tempnew.x = tempnew.x - floor(tempnew.x); 
    tempnew.y = jumpsize*((long double)rand()/((long double)RAND_MAX)-0.5)+s[pos].y;
    tempnew.y = tempnew.y - floor(tempnew.y); 
    tempnew.z = jumpsize*((long double)rand()/((long double)RAND_MAX)-0.5)+s[pos].z;
    tempnew.z = tempnew.z - floor(tempnew.z);
    tempnew.a = 2.0*PI*(long double)rand()/((long double)RAND_MAX);
    tempnew.b = acos(1.0-2.0*(((long double)rand())/((long double)RAND_MAX)));
    tempnew.c = 2.0*PI*(long double)rand()/((long double)RAND_MAX);
    tempnew.wellneighbors = 0;
    tempnew.currentwellneighbors = 0;
    tempnew.wellneighborssq = 0;
    //tempnew.wellneighbors = s[pos].wellneighbors;
    //tempnew.currentwellneighbors = s[pos].currentwellneighbors;
    //tempnew.wellneighborssq = s[pos].wellneighborssq;
    tempnew.patchneighbors = 0;
    tempnew.currentpatchneighbors = 0;
    tempnew.patchneighborssq = 0;
    //tempnew.patchneighbors = s[pos].patchneighbors;
    //tempnew.currentpatchneighbors = s[pos].currentpatchneighbors;
    //tempnew.patchneighborssq = s[pos].patchneighborssq;
    tempnew.mcount = s[pos].mcount;
    tempnew.ncount = s[pos].ncount;
    //calculate the new Boltzmann factor based on the new position
    newBoltzmann = productBoltzmann(s, &tempnew, pos, potentialRange);
    //calculate a random number between 0 and 1
    random = (long double)rand()/((long double)RAND_MAX);
    // If the oldBoltzmann factor is 0.0...
    if(oldBoltzmann == 0.0){
        s[pos].x = tempnew.x;
        s[pos].y = tempnew.y;
        s[pos].z = tempnew.z;
        s[pos].a = tempnew.a;
        s[pos].b = tempnew.b;
        s[pos].c = tempnew.c;
        s[pos].mcount++;
        numMoved++;
        s[pos].currentwellneighbors = tempnew.currentwellneighbors;
        s[pos].wellneighbors += tempnew.wellneighbors;
        s[pos].wellneighborssq += tempnew.wellneighborssq;
        s[pos].currentpatchneighbors = tempnew.currentpatchneighbors;
        s[pos].patchneighbors += tempnew.patchneighbors;
        s[pos].patchneighborssq += tempnew.patchneighborssq;
        s[pos].ncount = tempnew.ncount;
        if(!testing){
            totalneighbors += 2*(s[pos].currentwellneighbors + s[pos].currentpatchneighbors - oldneighbors);
            totalwellneighbors += 2*(s[pos].currentwellneighbors - oldwellneighbors);
            totalpatchneighbors += 2*(s[pos].currentpatchneighbors - oldpatchneighbors);
            if(totalneighbors < 0){
                exit(EXIT_FAILURE);
            }
        }
        etabar = ((double)totalneighbors)/((double)numSpheres);
        etabarwell = ((double)totalwellneighbors)/((double)numSpheres);
        etabarpatch = ((double)totalpatchneighbors)/((double)numSpheres);
//        if(s[pos].currentwellneighbors - oldneighbors < 0){
//            printf("hi there :)");
//        }
        //if(!testing && abs(totalneighborsprev - totalneighbors) > 20){
        if(!testing && (movenum % 1000 == 0)){
            fprintf(neighborout,"%d %ld %ld %ld\n ", movenum, totalneighbors, totalwellneighbors, totalpatchneighbors);
            totalneighborsprev = totalneighbors;
            totalwellneighborsprev = totalwellneighbors;
            totalpatchneighborsprev = totalpatchneighbors;
        }
        return;
    }
    //see if should accept the move
    if(random < (newBoltzmann/oldBoltzmann)){
        s[pos].x = tempnew.x;
        s[pos].y = tempnew.y;
        s[pos].z = tempnew.z;
        s[pos].a = tempnew.a;
        s[pos].b = tempnew.b;
        s[pos].c = tempnew.c;
        s[pos].mcount++;
        numMoved++;
        s[pos].currentwellneighbors = tempnew.currentwellneighbors;
        s[pos].wellneighbors += tempnew.wellneighbors;
        s[pos].wellneighborssq += tempnew.wellneighborssq;
        s[pos].currentpatchneighbors = tempnew.currentpatchneighbors;
        s[pos].patchneighbors += tempnew.patchneighbors;
        s[pos].patchneighborssq += tempnew.patchneighborssq;
        s[pos].ncount = tempnew.ncount;
        if(!testing){
            totalneighbors += 2*(s[pos].currentwellneighbors + s[pos].currentpatchneighbors - oldneighbors);
            totalwellneighbors += 2*(s[pos].currentwellneighbors - oldwellneighbors);
            totalpatchneighbors += 2*(s[pos].currentpatchneighbors - oldpatchneighbors);
            if(totalneighbors < 0){
                exit(EXIT_FAILURE);
            }
        }
        etabar = ((double)totalneighbors)/((double)numSpheres);
        etabarwell = ((double)totalwellneighbors)/((double)numSpheres);
        etabarpatch = ((double)totalpatchneighbors)/((double)numSpheres);
//        if(s[pos].currentwellneighbors - oldneighbors < 0){
//            printf("hi there :)");
//        }
        //if(!testing && abs(totalneighborsprev - totalneighbors) > 20){
        if(!testing && (movenum % 1000 == 0)){
            fprintf(neighborout,"%d %ld %ld %ld\n ", movenum, totalneighbors, totalwellneighbors, totalpatchneighbors);
            totalneighborsprev = totalneighbors;
            totalwellneighborsprev = totalwellneighbors;
            totalpatchneighborsprev = totalpatchneighbors;
        }
    }
    return;
}

/**
 * calculate the boltzmann factor
 * s is an array of spheres
 * test is the position around which to calculate the boltzmann factor
 * old is the index of the sphere to ignore
 * delta is the size of potential range	
 */
long double productBoltzmann(Sphere *s, Sphere *test, long old, long double delta){
    long wellcount=0, patchcount=0;
    int edgex=0, edgey=0, edgez=0;
    int patchfound=0;
    long double lengthSquared; 
    long double sx_min, sy_min, sz_min;
    long double sx_max, sy_max, sz_max;
    long double delta_x, delta_y, delta_z;  
    int i, gonewrong=0;
    //make sure that the delta is not bigger than half of the container
    if((2*delta)>1.0) exit(EXIT_FAILURE);

    //find out what boundaries a box around the test sphere should have
    sx_min = test->x - delta;
    sy_min = test->y - delta;
    sz_min = test->z - delta;
    sx_max = test->x + delta;
    sy_max = test->y + delta;
    sz_max = test->z + delta;

    if(sx_min<0){ sx_min+=1.0; edgex =1;}
    if(sy_min<0){ sy_min+=1.0; edgey =1;}
    if(sz_min<0){ sz_min+=1.0; edgez =1;}
    if(sx_max>1){ sx_max-=1.0; edgex =1;}
    if(sy_max>1){ sy_max-=1.0; edgey =1;}
    if(sz_max>1){ sz_max-=1.0; edgez =1;}
    //printf("x %Lf %Lf, y %Lf %Lf, z %Lf %Lf", sx_min, sx_max, sy_min, sy_max, sz_min, sz_max);

    //find the spheres inside the box
//#pragma omp parallel for default(shared) \
//    shared(s,test,old,delta,edgex,edgey,edgez,sx_min,sy_min,sz_min,sx_max,sy_max,sz_max,gonewrong) private(i,lengthSquared,delta_x,delta_y,delta_z) reduction(+:wellcount)
    for(i=0; i<numSpheres; i++){
        if((edgex==0 && s[i].x<= sx_max && s[i].x>= sx_min)||(edgex==1 
                    && (s[i].x<= sx_max || s[i].x>= sx_min))){
            //printf("The index of sphere inside x is %d\n", i);      
            if((edgey==0 && s[i].y<= sy_max && s[i].y>= sy_min)||(edgey==1 
                        && (s[i].y<= sy_max || s[i].y>= sy_min))){
                //printf("The index of sphere inside y is %d\n", i);
                if((edgez==0 && s[i].z<= sz_max && s[i].z>= sz_min)||(edgez==1 
                            && (s[i].z<= sz_max || s[i].z>= sz_min))){
                    if(i!=old){
                        //printf("The index of sphere inside this is %d\n", i);
                        if(s[i].x>=sx_min){
                            delta_x = s[i].x-(sx_min+delta);
                        }else{
                            delta_x = s[i].x-(sx_max-delta);
                        }
                        if(s[i].y>=sy_min){
                            delta_y = s[i].y-(sy_min+delta);
                        }else{
                            delta_y = s[i].y-(sy_max-delta);
                        }
                        if(s[i].z>=sz_min){
                            delta_z = s[i].z-(sz_min+delta);
                        }else{
                            delta_z = s[i].z-(sz_max-delta);
                        }
                        lengthSquared = delta_x*delta_x+delta_y*delta_y+delta_z*delta_z;
                        //if any are inside the hardCore of the sphere return 0            
                        if(lengthSquared<=hardCoreSquared) {
                            gonewrong++;
                            //return 0.0;
                        }
                        
                        //count how many are within the patch and in the square well
                        if(lengthSquared<=potentialRangeSquared && lengthSquared>=hardCoreSquared) {
                            //patchfound = patchWork(test, &s[i]);
                            if(patchfound == 0){
                                wellcount++;
                            } else {
                                patchcount++;
                            }
                            patchfound = 0;
                        }
                    }
                }
            }    
        }
    }
    if(gonewrong != 0) {
        return 0.0;
    }
    if(!testing){
        test->ncount++;
        test->wellneighbors += wellcount;
        test->currentwellneighbors = wellcount;
        test->wellneighborssq += pow(wellcount,2.0);
        test->patchneighbors += patchcount;
        test->currentpatchneighbors = patchcount;
        test->patchneighborssq += pow(patchcount,2.0);
    }
    //return the boltzmann factor
    long double boltzmannfactor = 0.0;
    //testing
    //boltzmannfactor += pow(exp(0.0*squareWellDepthBoltzmann[a]),wellcount);
    //boltzmannfactor += pow(exp(2.0*squareWellDepthBoltzmann[a]),patchcount);
    //standard
    boltzmannfactor += exp(wellcount*squareWellDepthBoltzmann[a] + patchcount*squarePatchDepthBoltzmann[a]);
    return boltzmannfactor;
}

/**
 * calculate the boltzmann factor
 * s is an array of spheres
 * test is the position around which to calculate the boltzmann factor
 * old is the index of the sphere to ignore
 * delta is the size of potential range	
 */
void countNeighbors(Sphere *s, Sphere *test, long old, long double delta){
    long wellcount=0, patchcount=0;
    int edgex=0, edgey=0, edgez=0;
    int patchfound=0;
    long double lengthSquared; 
    long double sx_min, sy_min, sz_min;
    long double sx_max, sy_max, sz_max;
    long double delta_x, delta_y, delta_z;  
    int i;
    //make sure that the delta is not bigger than half of the container
    if((2*delta)>1.0) exit(EXIT_FAILURE);

    //find out what boundaries a box around the test sphere should have
    sx_min = test->x - delta;
    sy_min = test->y - delta;
    sz_min = test->z - delta;
    sx_max = test->x + delta;
    sy_max = test->y + delta;
    sz_max = test->z + delta;

    if(sx_min<0){ sx_min+=1.0; edgex =1;}
    if(sy_min<0){ sy_min+=1.0; edgey =1;}
    if(sz_min<0){ sz_min+=1.0; edgez =1;}
    if(sx_max>1){ sx_max-=1.0; edgex =1;}
    if(sy_max>1){ sy_max-=1.0; edgey =1;}
    if(sz_max>1){ sz_max-=1.0; edgez =1;}

    //find the spheres inside the box
    for(i=0; i<numSpheres; i++){
        if((edgex==0 && s[i].x<= sx_max && s[i].x>= sx_min)||(edgex==1 
                    && (s[i].x<= sx_max || s[i].x>= sx_min))){
            if((edgey==0 && s[i].y<= sy_max && s[i].y>= sy_min)||(edgey==1 
                        && (s[i].y<= sy_max || s[i].y>= sy_min))){
                if((edgez==0 && s[i].z<= sz_max && s[i].z>= sz_min)||(edgez==1 
                            && (s[i].z<= sz_max || s[i].z>= sz_min))){
                    if(i!=old){
                        if(s[i].x>=sx_min){
                            delta_x = s[i].x-(sx_min+delta);
                        }else{
                            delta_x = s[i].x-(sx_max-delta);
                        }
                        if(s[i].y>=sy_min){
                            delta_y = s[i].y-(sy_min+delta);
                        }else{
                            delta_y = s[i].y-(sy_max-delta);
                        }
                        if(s[i].z>=sz_min){
                            delta_z = s[i].z-(sz_min+delta);
                        }else{
                            delta_z = s[i].z-(sz_max-delta);
                        }
                        lengthSquared = delta_x*delta_x+delta_y*delta_y+delta_z*delta_z;
                        //if any are inside the hardCore of the sphere return 0
                        if(lengthSquared<=hardCoreSquared) exit(EXIT_FAILURE);
                        //count how many are within the potential range 
                        if(lengthSquared<=potentialRangeSquared && lengthSquared>=hardCoreSquared) {
                            //patchfound = patchWork(test, &s[i]);
                            if(patchfound == 0){
                                wellcount++;
                            } else {
                                patchcount++;
                            }
                            patchfound = 0;
                        }
                    }
                }
            }    
        }
    }
    if(!testing){
        test->ncount++;
        test->wellneighbors += wellcount;
        test->currentwellneighbors = wellcount;
        test->wellneighborssq += pow(wellcount,2.0);
        test->patchneighbors += patchcount;
        test->currentpatchneighbors = patchcount;
        test->patchneighborssq += pow(patchcount,2.0);
    }
}

/**
 * Perform the necessary analytic geometry to determine patchy interactions
 */
int patchWork(Sphere *test, Sphere *si){
    // vector from center of test sphere to 'in potential range' neighbor sphere
    gsl_vector *v1 = gsl_vector_alloc(3);
    // head minus tail
    if(si->x-test->x > 0.5){
        gsl_vector_set(v1, 0, si->x - test->x - 1.0);
    }else if(si->x-test->x < -0.5){ 
        gsl_vector_set(v1, 0, si->x - test->x + 1.0);
    }else{
        gsl_vector_set(v1, 0, si->x - test->x);
    }
    if(si->y-test->y > 0.5){
        gsl_vector_set(v1, 1, si->y - test->y - 1.0);
    }else if(si->y-test->y < -0.5){ 
        gsl_vector_set(v1, 1, si->y - test->y + 1.0);
    }else{
        gsl_vector_set(v1, 1, si->y - test->y);
    }
    if(si->z-test->z > 0.5){
        gsl_vector_set(v1, 2, si->z - test->z - 1.0);
    }else if(si->z-test->z < -0.5){ 
        gsl_vector_set(v1, 2, si->z - test->z + 1.0);
    }else{
        gsl_vector_set(v1, 2, si->z - test->z);
    }
    // rotation matrix for returning v1 to standard basis 
    // (R^T to be used to actually perform the inverse rotation)
    gsl_matrix *R = gsl_matrix_alloc(3,3);
    gsl_matrix_set(R, 0, 0, cos(test->a)*cos(test->c)-cos(test->b)*sin(test->a)*sin(test->c));
    gsl_matrix_set(R, 0, 1, cos(test->c)*sin(test->a)+cos(test->a)*cos(test->b)*sin(test->c));
    gsl_matrix_set(R, 0, 2, sin(test->b)*sin(test->c));
    gsl_matrix_set(R, 1, 0, -cos(test->b)*cos(test->c)*sin(test->a)-cos(test->a)*sin(test->c));
    gsl_matrix_set(R, 1, 1, cos(test->a)*cos(test->b)*cos(test->c)-sin(test->a)*sin(test->c));
    gsl_matrix_set(R, 1, 2, cos(test->c)*sin(test->b));
    gsl_matrix_set(R, 2, 0, sin(test->a)*sin(test->b));
    gsl_matrix_set(R, 2, 1, -cos(test->a)*sin(test->b));
    gsl_matrix_set(R, 2, 2, cos(test->b));
    // identify the north pole
    // zpole = R(2,:) (bottom row of R, in other words right-most column R^T)
    gsl_vector *zpole = gsl_vector_alloc(3);
    gsl_vector_set(zpole, 0, hardCore/2.0*gsl_matrix_get(R, 2, 0));
    gsl_vector_set(zpole, 1, hardCore/2.0*gsl_matrix_get(R, 2, 1));
    gsl_vector_set(zpole, 2, hardCore/2.0*gsl_matrix_get(R, 2, 2));
    // rotate the north pole back to standard (for checking)
    // Rzpole = R.zpole
    gsl_vector *Rzpole = gsl_vector_alloc(3);
    gsl_vector_set_zero(Rzpole);
    gsl_blas_dgemv(CblasNoTrans, 1.0, R, zpole, 0.0, Rzpole);
    // vp = R.v1
    gsl_vector *vp1 = gsl_vector_alloc(3);
    gsl_vector_set_zero(vp1);
    gsl_blas_dgemv(CblasTrans, 1.0, R, v1, 0.0, vp1);
    // sc = radius/norm(vp)*vp
    gsl_vector *sc = gsl_vector_alloc(3);
    gsl_vector_set_zero(sc);
    gsl_vector_add(sc, vp1);
    gsl_vector_scale(sc, (hardCore/2.0)/gsl_blas_dnrm2(vp1));
    // l = 1/2*vp + Rzpole
    gsl_vector *l = gsl_vector_alloc(3);
    gsl_vector_set_zero(l);
    gsl_blas_daxpy(0.5, vp1, l);
    gsl_blas_daxpy(1.0, Rzpole, l);
    // Gram-Schmidt orthonormalization
    // m = l - <l,sc>/<sc,sc>*sc
    gsl_vector *m = gsl_vector_alloc(3);
    gsl_vector_set_zero(m);
    gsl_blas_daxpy(1.0, l, m);
    double ldotsc = 0.0;
    double scdotsc = 0.0;
    gsl_blas_ddot(l, sc, &ldotsc);
    gsl_blas_ddot(sc, sc, &scdotsc);
    gsl_blas_daxpy(-1.0*ldotsc/scdotsc, sc, m);
    // Rm = R.m
    gsl_vector *Rm = gsl_vector_alloc(3);
    gsl_vector_set_zero(Rm);
    gsl_blas_dgemv(CblasNoTrans, 1.0, R, m, 0.0, Rm);

    // testing output
    /*
       int i1 = 0, j1 = 0;
       printf("\nlengthSquared:%3.10Lf",lengthSquared);
       printf("\npotentialRangeSquared:%3.10Lf",potentialRangeSquared);
       printf("\nhardCoreSquared:%3.10Lf",hardCoreSquared);
       printf("\ntest:\n");
       printf("x=%3.10Lf, y=%3.10Lf, z=%3.10Lf\n", test->x, test->y, test->z);
       printf("a=%3.10Lf, b=%3.10Lf, c=%3.10Lf\n", test->a, test->b, test->c);
       printf("\ns[%d]:\n",i);
       printf("x=%3.10Lf, y=%3.10Lf, z=%3.10Lf\n", si->x, si->y, si->z);
       printf("a=%3.10Lf, b=%3.10Lf, c=%3.10Lf\n", si->a, si->b, si->c);
       printf("\nR:\n");
       for(i1 = 0; i1 < 3; i1++){
       for(j1 = 0; j1 < 3; j1++){
       printf("%3.10f ", gsl_matrix_get(R,i1,j1));
       }
       printf("\n");
       }
       printf("\nv1:\n");
       for(i1 = 0; i1 < 3; i1++){
       printf("%3.10f \n", gsl_vector_get(v1,i1));
       }
       printf("\nvp:\n");
       for(i1 = 0; i1 < 3; i1++){
       printf("%3.10f \n", gsl_vector_get(vp,i1));
       }
       printf("\nzpole:\n");
       for(i1 = 0; i1 < 3; i1++){
       printf("%3.10f \n", gsl_vector_get(zpole,i1));
       }
       printf("\nRzpole:\n");
       for(i1 = 0; i1 < 3; i1++){
       printf("%3.10f \n", gsl_vector_get(Rzpole,i1));
       }
       printf("\nsc:\n");
       for(i1 = 0; i1 < 3; i1++){
       printf("%3.10f \n", gsl_vector_get(sc,i1));
       }
       printf("\nl:\n");
       for(i1 = 0; i1 < 3; i1++){
       printf("%3.10f \n", gsl_vector_get(l,i1));
       }
       printf("\nprojsc:%f\n",-1.0*ldotsc/scdotsc);
       printf("\nRm:\n");
       for(i1 = 0; i1 < 3; i1++){
       printf("%3.10f \n", gsl_vector_get(Rm,i1));
       }
     */


    // free for reuse
    //gsl_vector_free(v);
    //gsl_vector_free(vp1);
    gsl_vector_free(l);
    gsl_vector_free(sc);
    gsl_vector_free(zpole);
    gsl_vector_free(Rzpole);
    gsl_matrix_free(R);

    gsl_vector *v2 = gsl_vector_alloc(3);
    // tail minus head (looking at other sphere now)
    if(test->x-si->x > 0.5){
        gsl_vector_set(v2, 0, test->x - si->x - 1.0);
    }else if(test->x-si->x < -0.5){ 
        gsl_vector_set(v2, 0, test->x - si->x + 1.0);
    }else{
        gsl_vector_set(v2, 0, test->x - si->x);
    }
    if(test->y-si->y > 0.5){
        gsl_vector_set(v2, 1, test->y - si->y - 1.0);
    }else if(test->y-si->y < -0.5){ 
        gsl_vector_set(v2, 1, test->y - si->y + 1.0);
    }else{
        gsl_vector_set(v2, 1, test->y - si->y);
    }
    if(test->z-si->z > 0.5){
        gsl_vector_set(v2, 2, test->z - si->z - 1.0);
    }else if(test->z-si->z < -0.5){ 
        gsl_vector_set(v2, 2, test->z - si->z + 1.0);
    }else{
        gsl_vector_set(v2, 2, test->z - si->z);
    }
    // rotation matrix for returning v2 to standard basis 
    // (R^T to be used to actually perform the inverse rotation)
    R = gsl_matrix_alloc(3,3);
    gsl_matrix_set(R, 0, 0, cos(si->a)*cos(si->c)-cos(si->b)*sin(si->a)*sin(si->c));
    gsl_matrix_set(R, 0, 1, cos(si->c)*sin(si->a)+cos(si->a)*cos(si->b)*sin(si->c));
    gsl_matrix_set(R, 0, 2, sin(si->b)*sin(si->c));
    gsl_matrix_set(R, 1, 0, -cos(si->b)*cos(si->c)*sin(si->a)-cos(si->a)*sin(si->c));
    gsl_matrix_set(R, 1, 1, cos(si->a)*cos(si->b)*cos(si->c)-sin(si->a)*sin(si->c));
    gsl_matrix_set(R, 1, 2, cos(si->c)*sin(si->b));
    gsl_matrix_set(R, 2, 0, sin(si->a)*sin(si->b));
    gsl_matrix_set(R, 2, 1, -cos(si->a)*sin(si->b));
    gsl_matrix_set(R, 2, 2, cos(si->b));
    // identify the north pole
    // zpole = R(2,:) (bottom row of R, in other words right-most column R^T)
    zpole = gsl_vector_alloc(3);
    gsl_vector_set(zpole, 0, hardCore/2.0*gsl_matrix_get(R, 2, 0));
    gsl_vector_set(zpole, 1, hardCore/2.0*gsl_matrix_get(R, 2, 1));
    gsl_vector_set(zpole, 2, hardCore/2.0*gsl_matrix_get(R, 2, 2));
    // rotate the north pole back to standard (for checking)
    // Rzpole = R.zpole
    Rzpole = gsl_vector_alloc(3);
    gsl_vector_set_zero(Rzpole);
    gsl_blas_dgemv(CblasNoTrans, 1.0, R, zpole, 0.0, Rzpole);
    // vp = R.v2
    gsl_vector *vp2 = gsl_vector_alloc(3);
    gsl_vector_set_zero(vp2);
    gsl_blas_dgemv(CblasTrans, 1.0, R, v2, 0.0, vp2);
    // sc = radius/norm(vp)*vp
    sc = gsl_vector_alloc(3);
    gsl_vector_set_zero(sc);
    gsl_vector_add(sc, vp2);
    gsl_vector_scale(sc, (hardCore/2.0)/gsl_blas_dnrm2(vp2));
    // l = 1/2*vp + Rzpole
    l = gsl_vector_alloc(3);
    gsl_vector_set_zero(l);
    gsl_blas_daxpy(0.5, vp2, l);
    gsl_blas_daxpy(1.0, Rzpole, l);
    // Gram-Schmidt orthonormalization
    // n = l - <l,sc>/<sc,sc>*sc
    gsl_vector *n = gsl_vector_alloc(3);
    gsl_vector_set_zero(n);
    gsl_blas_daxpy(1.0, l, n);
    ldotsc = 0.0;
    scdotsc = 0.0;
    gsl_blas_ddot(l, sc, &ldotsc);
    gsl_blas_ddot(sc, sc, &scdotsc);
    gsl_blas_daxpy(-1.0*ldotsc/scdotsc, sc, n);
    // Rn = R.n
    gsl_vector *Rn = gsl_vector_alloc(3);
    gsl_vector_set_zero(Rn);
    gsl_blas_dgemv(CblasNoTrans, 1.0, R, n, 0.0, Rn);

    // testing output for verifying matrix computations
    /*
       printf("\ntest:\n");
       printf("x=%3.10Lf, y=%3.10Lf, z=%3.10Lf\n", test->x, test->y, test->z);
       printf("a=%3.10Lf, b=%3.10Lf, c=%3.10Lf\n", test->a, test->b, test->c);
       printf("\ns[%d]:\n",i);
       printf("x=%3.10Lf, y=%3.10Lf, z=%3.10Lf\n", si->x, si->y, si->z);
       printf("a=%3.10Lf, b=%3.10Lf, c=%3.10Lf\n", si->a, si->b, si->c);
       printf("\nR:\n");
       for(i1 = 0; i1 < 3; i1++){
       for(j1 = 0; j1 < 3; j1++){
       printf("%3.10f ", gsl_matrix_get(R,i1,j1));
       }
       printf("\n");
       }
       printf("\nv2:\n");
       for(i1 = 0; i1 < 3; i1++){
       printf("%3.10f \n", gsl_vector_get(v2,i1));
       }
       printf("\nvp:\n");
       for(i1 = 0; i1 < 3; i1++){
       printf("%3.10f \n", gsl_vector_get(vp,i1));
       }
       printf("\nzpole:\n");
       for(i1 = 0; i1 < 3; i1++){
       printf("%3.10f \n", gsl_vector_get(zpole,i1));
       }
       printf("\nRzpole:\n");
       for(i1 = 0; i1 < 3; i1++){
       printf("%3.10f \n", gsl_vector_get(Rzpole,i1));
       }
       printf("\nsc:\n");
       for(i1 = 0; i1 < 3; i1++){
       printf("%3.10f \n", gsl_vector_get(sc,i1));
       }
       printf("\nl:\n");
       for(i1 = 0; i1 < 3; i1++){
       printf("%3.10f \n", gsl_vector_get(l,i1));
       }
       printf("\nprojsc:%f\n",-1.0*ldotsc/scdotsc);
       printf("\nRn:\n");
       for(i1 = 0; i1 < 3; i1++){
       printf("%3.10f \n", gsl_vector_get(Rn,i1));
       }
     */

    // initialize
    double dotp1 = 0.0;
    double dotp2 = 0.0;
    double dotp3 = 0.0;
    double dotp4 = 0.0;
    double norm1 = 0.0;
    double norm2 = 0.0;
    double norm3 = 0.0;
    double norm4 = 0.0;

    // Calculate thetas 1 and 2
    double theta1 = 0.0;
    double theta2 = 0.0;
    gsl_blas_ddot(vp1,Rzpole,&dotp1);
    gsl_blas_ddot(vp2,Rzpole,&dotp2);
    norm1 = gsl_blas_dnrm2(vp1);
    norm2 = gsl_blas_dnrm2(vp2);
    norm3 = gsl_blas_dnrm2(Rzpole);
    theta1 = acos(dotp1/(norm1*norm3))*180.0/PI;
    theta2 = acos(dotp2/(norm2*norm3))*180.0/PI;

    // reinitialize
    dotp1 = 0.0;
    dotp2 = 0.0;
    dotp3 = 0.0;
    dotp4 = 0.0;
    norm1 = 0.0;
    norm2 = 0.0;
    norm3 = 0.0;
    norm4 = 0.0;

    // Calculate phis 1 and 2
    double phi1 = 0.0;
    double phi2 = 0.0;
    double phi3 = 0.0;
    double phi4 = 0.0;
    gsl_vector *vp1proj = gsl_vector_alloc(3);
    gsl_vector_set(vp1proj, 0, gsl_vector_get(vp1,0));
    gsl_vector_set(vp1proj, 1, gsl_vector_get(vp1,1));
    gsl_vector_set(vp1proj, 2, 0.0);
    gsl_vector *vp2proj = gsl_vector_alloc(3);
    gsl_vector_set(vp2proj, 0, gsl_vector_get(vp2,0));
    gsl_vector_set(vp2proj, 1, gsl_vector_get(vp2,1));
    gsl_vector_set(vp2proj, 2, 0.0);
    gsl_vector *xaxis = gsl_vector_alloc(3);
    gsl_vector *yaxis = gsl_vector_alloc(3);
    gsl_vector_set_zero(xaxis);
    gsl_vector_set_zero(yaxis);
    gsl_vector_set(xaxis, 0, 1.0);
    gsl_vector_set(yaxis, 1, 1.0);
    gsl_blas_ddot(vp1proj, xaxis, &dotp1);
    gsl_blas_ddot(vp2proj, xaxis, &dotp2);
    gsl_blas_ddot(vp1proj, yaxis, &dotp3);
    gsl_blas_ddot(vp2proj, yaxis, &dotp4);
    norm1 = gsl_blas_dnrm2(vp1proj);
    norm2 = gsl_blas_dnrm2(vp2proj);
    norm3 = gsl_blas_dnrm2(xaxis);
    norm4 = gsl_blas_dnrm2(yaxis);
    phi1 = acos(dotp1/(norm1*norm3))*180.0/PI;
    phi2 = acos(dotp2/(norm2*norm3))*180.0/PI;
    phi3 = acos(dotp3/(norm1*norm4))*180.0/PI;
    phi4 = acos(dotp4/(norm2*norm4))*180.0/PI;

    // reinitialize
    dotp1 = 0.0;
    dotp2 = 0.0;
    dotp3 = 0.0;
    dotp4 = 0.0;
    norm1 = 0.0;
    norm2 = 0.0;
    norm3 = 0.0;
    norm4 = 0.0;

    // Calculate omega
    double omega1 = 0.0;
    double omega2 = 0.0;
    // -a x b = (-a2b3 + a3b2, -a3b1 + a1b3, -a1b2 + a2b1).
    gsl_vector *cross = gsl_vector_alloc(3);
    gsl_vector_set_zero(cross);
    gsl_vector_set(cross, 0, -gsl_vector_get(Rm,1)*gsl_vector_get(v1,2) + gsl_vector_get(Rm,2)*gsl_vector_get(v1,1));
    gsl_vector_set(cross, 1, -gsl_vector_get(Rm,2)*gsl_vector_get(v1,0) + gsl_vector_get(Rm,0)*gsl_vector_get(v1,2));
    gsl_vector_set(cross, 2, -gsl_vector_get(Rm,0)*gsl_vector_get(v1,1) + gsl_vector_get(Rm,1)*gsl_vector_get(v1,0));
    gsl_blas_ddot(Rm,Rn,&dotp1);
    gsl_blas_ddot(cross,Rn,&dotp2);
    gsl_blas_ddot(cross,Rm,&dotp3);
    norm1 = gsl_blas_dnrm2(Rm);
    norm2 = gsl_blas_dnrm2(Rn);
    norm3 = gsl_blas_dnrm2(cross);
    omega1 = acos(dotp1/(norm1*norm2))*180.0/PI;
    omega2 = acos(dotp2/(norm2*norm3))*180.0/PI;

    gsl_vector_free(v1);
    gsl_vector_free(v2);
    gsl_vector_free(vp1);
    gsl_vector_free(vp2);
    gsl_vector_free(vp1proj);
    gsl_vector_free(vp2proj);
    gsl_vector_free(xaxis);
    gsl_vector_free(yaxis);
    gsl_vector_free(cross);
    gsl_vector_free(l);
    gsl_vector_free(sc);
    gsl_vector_free(zpole);
    gsl_vector_free(Rzpole);
    gsl_vector_free(m);
    gsl_vector_free(n);
    gsl_vector_free(Rm);
    gsl_vector_free(Rn);
    gsl_matrix_free(R);

    //exit(0);

    // simple dimers 
    if((theta1 < 30.0) &&
       (theta2 < 30.0)){
    // complex (locked planar) trimers
    //if(fabs(theta1 - 90.0) < 20.0 && (fabs(phi1) < 20.0 || fabs(phi1-60.0) < 20.0) && omega1 < 20.0){
    // complex (locked planar) tetramers
    //if(fabs(theta1 - 90.0) < 20.0 && (fabs(phi1) < 20.0 || fabs(phi1-90.0) < 20.0) && omega1 < 20.0){
    // simple polymer chains 
    //if((theta1 < 20.0 || theta1 > 160.0) &&
    //  (theta2 < 20.0 || theta2 > 160.0)){
    // complex (magnetic N-S) polymer chains
    //if((((theta1 < 20.0) && (phi1 < 360.0) && (omega < 360.0)) &&
    //  ((theta2 > 160.0) && (phi2 < 360.0) && (omega < 360.0))) ||
    //  (((theta2 < 20.0) && (phi2 < 360.0) && (omega < 360.0)) &&
    //  ((theta1 > 160.0) && (phi1 < 360.0) && (omega < 360.0)))){
    // helices
    //if( ((fabs(theta1-45.0) < 15.0 && fabs(phi1-45.0) < 15.0 && fabs(phi3) < 90.0 && fabs(omega1-90.0) < 15.0 && fabs(omega2) < 90.0) &&
    //         (fabs(theta2-135.0) < 15.0 && fabs(phi2-135.0) < 15.0 && fabs(phi4) > 90.0 && fabs(omega1-90.0) < 15.0 && fabs(omega2) < 90.0)) ||
    //        ((fabs(theta2-45.0) < 15.0 && fabs(phi2-45.0) < 15.0 && fabs(phi4) < 90.0 && fabs(omega1-90.0) < 15.0 && fabs(omega2) < 90.0) &&
    //         (fabs(theta1-135.0) < 15.0 && fabs(phi1-135.0) < 15.0 && fabs(phi3) > 90.0 && fabs(omega1-90.0) < 15.0 && fabs(omega2) < 90.0)) ){
        return 1;
    } else {
        return 0;
    }
}
