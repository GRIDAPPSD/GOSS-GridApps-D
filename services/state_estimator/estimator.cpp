// ActiveMQ Dependancies
#include <activemq/library/ActiveMQCPP.h>
#include "my_activeMQ.hpp"
// END ActiveMQ Dependancies


// SuiteSparse Dependancies
#include "klu.h"
#include "cs.h"
// END SuiteSparse Dependancies


#include <complex>
#include <string>
#include <iostream>
#include <fstream>

#define uint unsigned int


// Aliases for vector data types
#include <vector>
#define DVEC std::vector<double>
#define CVEC std::vector<std::complex<double>>
#define SVEC std::vector<std::string>


// Store node names in a linked list and hash node name to their position
#include <list>
#define SLST std::list<std::string>
#include <unordered_map>
#define SMAP std::unordered_map<std::string,unsigned int>

// Hash address (i,j) to the index of a sparse matrix vector
#define UMAP std::unordered_map<unsigned int,unsigned int>
#define MMAP std::unordered_map<unsigned int,UMAP>

#define CMAP std::unordered_map<unsigned int, std::complex<double>>
#define CMMP std::unordered_map<unsigned int,CAP>

// Store x and z in a list indexed by 


/*
#include <array>
// #define DARY = std::array<double>
*/


int main(void) {
	try {
		// --------------------------------------------------------------------
		// INITIALIZATION
		// --------------------------------------------------------------------
		
		std::cout<<"Begin initialization...\n";

		// READ CONFIGURATOIN FILE
		//  - Determine mode
		//  - Determine 
		

		
		/*
		// --------------------------------------------------------------------
		// START ACTIVEMQ
		// --------------------------------------------------------------------
		activemq::library::ActiveMQCPP::initializeLibrary();
		std::cout << "=====================================================\n";
	    std::cout << "Starting the example:" << std::endl;
	    std::cout << "-----------------------------------------------------\n";
		// Set the URI to point to the IP Address of your broker.
	    // add any optional params to the url to enable things like
	    // tightMarshalling or tcp logging etc.  See the CMS web site for
	    // a full list of configuration options.
	    //
	    //  http://activemq.apache.org/cms/
	    //
	    // Wire Format Options:
	    // =========================
	    // Use either stomp or openwire, the default ports are different for each
	    //
	    // Examples:
	    //    tcp://127.0.0.1:61616                      default to openwire
	    //    tcp://127.0.0.1:61616?wireFormat=openwire  same as above
	    //    tcp://127.0.0.1:61613?wireFormat=stomp     use stomp instead
	    //
	    // SSL:
	    // =========================
	    // To use SSL you need to specify the location of the trusted Root CA or the
	    // certificate for the broker you want to connect to.  Using the Root CA allows
	    // you to use failover with multiple servers all using certificates signed by
	    // the trusted root.  If using client authentication you also need to specify
	    // the location of the client Certificate.
	    //
    	//     System::setProperty( "decaf.net.ssl.keyStore", "<path>/client.pem" );
    	//     System::setProperty( "decaf.net.ssl.keyStorePassword", "password" );
    	//     System::setProperty( "decaf.net.ssl.trustStore", "<path>/rootCA.pem" );
    	//
    	// The you just specify the ssl transport in the URI, for example:
    	//
    	//     ssl://localhost:61617
    	//
	    std::string brokerURI =
        "failover:(tcp://WE33461.pnl.gov:61616"
//        "?wireFormat=openwire"
//        "&transport.useInactivityMonitor=false"
//        "&connection.alwaysSyncSend=true"
//        "&connection.useAsyncSend=true"
//        "?transport.commandTracingEnabled=true"
//        "&transport.tcpTracingEnabled=true"
//        "&wireFormat.tightEncodingEnabled=true"
        ")";

	    //============================================================
	    // set to true to use topics instead of queues
	    // Note in the code above that this causes createTopic or
	    // createQueue to be used in both consumer an producer.
	    //============================================================
	    bool useTopics = true;
	    bool sessionTransacted = false;
	    int numMessages = 100;
	
	    long long startTime = System::currentTimeMillis();
	
    	HelloWorldProducer producer(brokerURI, numMessages, useTopics);
    	HelloWorldConsumer consumer(brokerURI, numMessages, useTopics, sessionTransacted);

	    // Start the consumer thread.
	    Thread consumerThread(&consumer);
	    consumerThread.start();
		std::cout<<"consumer thread started\n";
	
	    // Wait for the consumer to indicate that its ready to go.
	    consumer.waitUntilReady();
	
	    // Start the producer thread.
		Thread producerThread(&producer);
   		producerThread.start();
		std::cout<<"producer thread started\n";
	
	    // Wait for the threads to complete.
	    producerThread.join();
	    consumerThread.join();
	
	    long long endTime = System::currentTimeMillis();
	    double totalTime = (double)(endTime - startTime) / 1000.0;
	
	    consumer.close();
	    producer.close();
		
		std::cout << "Time to completion = " << totalTime << " seconds." << std::endl;
   		std::cout << "-----------------------------------------------------\n";
   		std::cout << "Finished with the example." << std::endl;
   		std::cout << "=====================================================\n";
	
   		activemq::library::ActiveMQCPP::shutdownLibrary();
		*/
		
		
		
		// --------------------------------------------------------------------
		// PROCESS TOPOLOGY
		// --------------------------------------------------------------------

		// BUILD NODE LIST STRUCTURES
		SLST nodens; 	// tracks all node names in order
		SMAP nodem;		// maps from node name to 1-indexed position
		uint numns = 0;	// number nodes
		// to add a node:
		//	-- nodens.push_back(noden);
		//	-- nodem[ndoen] = ++numns;


		// For now, pull this in from a file:
		//	base_nodelist.csv from dss cmd "export ynodelist base_nodelist.csv"
		std::ifstream nfs;
		nfs.open("demo/13Bus/base_nodelist.csv",std::ifstream::in);
		if ( !nfs ) throw "failed to open node name file";
		std::string nfsl;
		while ( std::getline(nfs,nfsl) ) {
			// strip leading and trailing quotations and white space
			std::string noden = nfsl.substr(nfsl.find_first_not_of("\'\""),
					nfsl.find_last_not_of(" \t\f\v\n\r\'\""));
			//std::cout << "|" << noden << "|\n";
			nodens.push_back(noden);
			nodem[noden] = ++numns;
		}
		nfs.close();
		// END pull node list from file


//		// print back nodens and their positiions from nodem
//		for ( auto itr = nodens.begin() ; itr != nodens.end() ; itr++ ) 
//			cout << "Node |" << *itr << "| -> " << nodem[*itr] << '\n';



//		// BUILD THE ADMITTANCE MATRIX STRUCTURES
//		CVEC Y;			// this linear vector stores sparse Ybus entries
//		MMAP Ym;		// This 2D map maps row and colum indices to Y
//		// To append an element:
//		//	-- Ym[i][j] = Y.size();
//		//	-- Y.push_back(std::complex<double>(G,B));
//		// G, B, g, and b are derived from Y:
//		//	-- Gij = std::real(Y[Ym[i][j]]);
//		//	-- Bij = std::imag(Y[Ym[i][j]]);
//		//	-- gij = std::real(-1.0*Y[Ym[i][j]]);
//		//	-- bij = std::imag(-1.0*Y[Ym[i][j]]);

		CMMP YY;		// two-dimensional sparse matrix
		
		


		// For now, pull the ybus from a file:
		// base_ysparse.csv from dss cmd "export y triplet base_ysparse.csv"
		std::ifstream yfs;
		//yfs.open("demo/4node/base_ysparse.csv",std::ifstream::in);
		yfs.open("demo/13Bus/base_ysparse.csv",std::ifstream::in);
		if ( !yfs ) throw "failed to open ybus file";
		std::string yfsl;
		std::getline(yfs,yfsl);		// skip the header
		//std::cout<<yfsl<<'\n';		// print back the header
		int i,j;
		double G,B;
		char c;
		while ( yfs >> i >> c >> j >> c >> G >> c >> B ) {
			cout << i << '\t' << j << '\t' << G << '\t' << B << '\n';
//			Ym[i][j] = Y.size();
//			if ( i != j ) Ym[j][i] = Y.size();
//			Y.push_back(std::complex<double>(G,B));
			YY[i][j] = std::complex<double>(G,B));
			if ( i != j ) YY[j][i] = std::complex<double(G,B));
		}
		yfs.close();
		// END pull ybus from file


		cout << "Y[1][1] = " << Y[1][1] << '\n';
		cout << "Y[35][36] = " << Y[35][36] << '\n';
		throw "debugging: end YY test";
		
//		// this accesses the sparse data vector Y directly
//		for ( auto itr=Y.begin() ; itr!=Y.end() ; itr++ )
//			cout << *itr << '\n';
		
//		// this provides random access sparse elements in Y:
//		cout << "Y[1][1] = " <<	Y[Ym[1][1]] << '\n';
//		cout << "Y[35][36] = " << Y[Ym[35][36]] << '\n';

//		// list the populated index pairs in Ym:
//		for ( auto itr=Ym.begin() ; itr!=Ym.end() ; itr++ ) {
//			int i = std::get<0>(*itr);
//			cout << "columns in row " << i << ";\n\t";
//			for ( auto jtr=Ym[i].begin() ; jtr!=Ym[i].end() ; jtr++ ) {
//				int j = std::get<0>(*jtr);
//				cout << j << '\t';
//			}
//			cout << '\n';
//		}


		// --------------------------------------------------------------------
		// INITIALIZE METER INTERFACE
		// --------------------------------------------------------------------

		// INITIALIZE THE STATE VECTOR
		vnom = 0.0;	// get this from the CIM?
		DVEC xV;	// vector of voltage magnitude states
		DVEC xT;	// vector of voltage angle states
		for ( int idx = 0 ; idx < numns ; idx++ ) {
			xV.push_back(vnom);
			xT.push_back(0);
		}
		int xqty = xV.size() + xT.size();
		
		
		// INITIALIZE THE MEASUREMENT VECTOR
		// Determine the size of the measurement vector
		DVEC sense;
		DVEC ssigs;
		SVEC sname;
		// for ( /* sensor objects */ ) {
			// z.append(0.0);
			// sigs.append(sensor.std_dev());
			// zn.append(/*JSON ADDRESS OF MEASUREMENT*/);
		// }
		int zqty = sense.size();
		
		
		// INITIALIZE THE MEASUREMENT FUNCTION h(x)
		enum hx_t {
			Pij ,
			Qij ,
			Pi ,
			Qi };
		DVEC hx;
		std::vector<hx_t> thx;
		std::vector<uint> hxi;
		std::vector<std::vector<uint>> hxj;
		for ( int ii = 0 ; ii < zqty ; ii++ ) {
			// for each measurement:
			// hx.append(initial value)
			// thx.append(type [hx_t])
			// if ( branch ) {
				// hxi.append( i );
				// hxj.append( (vector)(j) );
			// }
			// if ( bus ) {
				// hxi.append( i );
				// hxj.append( A[i] ); // from adjacency matrix
			// }
			// we should actually probably store the nodename or xidx
		}
		
		// INITIALIZE THE MEASUREMENT FUNCTION JACOBIAN J(x)
		enum Jx_t {
			dPijdVi , dPijdVj , dPijdTi , dPijdTj , 	
			dQijdVi , dQijdVj , dQijdTi , dQijdTj , 
			dPidVi  , dPidVj  , dPidTi  , dPidTj  ,
			dQidVi  , dQidVj  , dQidTi  , dQidTj  };
		DVEC Jx;
		std::vector<Jx_t> tJx;
		std::vector<uint> Jxi;
		std::vector<std::vector<uint>> Jxj;
		for ( int ii = 0 ; ii < zqty ; ii++ ) {
			// for each measurement function:
			for ( int jj = 0 ; jj < xqty ; jj ++ ) {
				// We might want to have established a unified state vector by now
				// establish the derivetive with respect to each state
				// Jx.append(initial value)
				// tJx.append(type [Jx_t])
				// i???
				// j???
				// rows correspond to measurements
				// columns correspond to derivatives with respect to states
			}
		}
		
		// Handoff from the topology processor to the state estimator
		// --------------------------------------------------------------------
		// INTERNAL VARIABLE INITIALIZATION
		// --------------------------------------------------------------------
		// Initialize State Vector x
		// cs_spalloc(m,n,nzmax,values,triplet)
		cs *xraw = cs_spalloc(0,0,xqty,1,1);
		for ( int ii = 0 ; ii < xV.size() ; ii++ )
			cs_entry(xraw,ii,0,xV[ii]);
		for ( int ii = 0 ; ii < xT.size() ; ii++ )
			cs_entry(xraw,xV.size()+ii,0,xT[ii]);
		cs *x = cs_compress(xraw); cs_spfree(xraw);
		
		// Initialize measurement covariance matrix R
		// cs_spalloc(m,n,nzmax,values,triplet)
		cs *Rraw = cs_spalloc(0,0,zqty,1,1);
		for ( int ii = 0 ; ii < zqty ; ii++ )
			cs_entry(Rraw,ii,ii,ssigs[ii]);
		cs *R = cs_compress(Rraw); cs_spfree(Rraw);
		
		// State transition matrix F
		// cs_spalloc(m,n,nzmax,values,triplet)
		cs *Fraw = cs_spalloc(0,0,xqty,1,1);
		for ( int ii = 0 ; ii < xqty ; ii++ )
			cs_entry(Fraw,ii,ii,1.0);
		cs *F = cs_compress(Fraw); cs_spfree(Fraw);
		
		// Process noise covariance matrix Q
		// cs_spalloc(m,n,nzmax,values,triplet)
		cs *Qraw = cs_spalloc(0,0,xqty,1,1);
		for ( int ii = 0 ; ii < xqty ; ii++ )
			cs_entry(Qraw,ii,ii,0.04*sqrt(1.0/4));
		cs *Q = cs_compress(Qraw); cs_spfree(Qraw);
		
		// Identity matrix of dimention of x eyex
		// cs_spalloc(m,n,nzmax,values,triplet)
		cs *eyexraw = cs_spalloc(0,0,xqty,1,1);
		for ( int ii = 0 ; ii < xqty ; ii++ )
			cs_entry(eyexraw,ii,ii,1.0);
		cs *eyex = cs_compress(eyexraw); cs_spfree(eyexraw);
		
		// Identity matrix of dimention of z eyez
		// cs_spalloc(m,n,nzmax,values,triplet)
		cs *eyezraw = cs_spalloc(0,0,zqty,1,1);
		for ( int ii = 0 ; ii < zqty ; ii++ )
			cs_entry(eyexraw,ii,ii,1.0);
		cs *eyez = cs_compress(eyezraw); cs_spfree(eyezraw);
		
		// Initialized error covariance matrix P
		cs *Praw = cs_spalloc(0,0,xqty*xqty,1,1);
		// initialize to zero on a cold start?
		cs *P = cs_compress(Praw); cs_spfree(Praw);
		
		
		
		// --------------------------------------------------------------------
		// STATE ESTIMATOR LOOP
		// --------------------------------------------------------------------
		std::cout<<"Begin estimator loop...\n";
		bool quit = false;
		while(!quit) {
			// ----------------------------------------------------------------
			// Check for New Measurements
			// ----------------------------------------------------------------
			while ( 0 /* check for new measurements */ ) {
				// #include <chrono>
				// #include <thread>
				// std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			}
			
			
			// ----------------------------------------------------------------
			// Read Measurements
			// ----------------------------------------------------------------
			for( int ii = 0 ; ii < sense.size() ; ii++ ) {
				// if ( /* sname[ii] in json */ ) {
					// sense[ii] = json[sname[ii]];
				// }
			}
			
			// ----------------------------------------------------------------
			// Update Measurement Function h(x)
			// ----------------------------------------------------------------
			for ( int idx = 0 ; idx < hx.size() ; idx++ ) {
				uint i = hxi[idx];
				std::vector<uint> js = hxj[idx];
				if ( Pij == thx[idx] ) {
					uint j = js[0];
					double Tij = xT[i] - xT[j];
					double gij = std::real(-1.0*Ym[i][j]);
					double bij = std::imag(-1.0*Ym[i][j]);
					hx[idx] = xV[i]*xV[i]*gij - xV[i]*xV[j] * 
						( gij*cos(Tij) + bij*sin(Tij) );
				}
				else if ( thx[idx] == Qij ) {
					uint j = js[0];
					double Tij = xT[i] - xT[j];
					double gij = std::real(-1.0*Ym[i][j]);
					double bij = std::imag(-1.0*Ym[i][j]);
					hx[idx] = -1.0*xV[i]*xV[i]*bij - xV[i]*xV[j] * 
						( gij*sin(Tij) - bij*cos(Tij) );
				}
				else if ( thx[idx] == Pi ) {
					double h = 0;
					for ( uint jdx = 0 ; jdx < js.size() ; jdx++ ) {
						uint j = js[jdx];
						double Tij = xT[i] - xT[j];
						double Gij = std::real(Ym[i][j]);
						double Bij = std::imag(Ym[i][j]);
						h += xV[j] * ( Gij*cos(Tij) + Bij*sin(Tij) );
					}
					hx[idx] = h * xV[i];
				}
				else if ( thx[idx] == Qi ) {
					double h = 0;
					for ( unsigned int jdx = 0 ; jdx < js.size() ; jdx++ ) {
						uint j = js[jdx];
						double Tij = xT[i] - xT[j];
						double Gij = std::real(Ym[i][j]);
						double Bij = std::imag(Ym[i][j]);
						h += xV[j] * ( Gij*sin(Tij) - Bij*cos(Tij) );
					}
					hx[idx] = h * xV[i];
				}
			}
			
			
			// ----------------------------------------------------------------
			// Update Measurement Jacobian H(x)
			// ----------------------------------------------------------------
			for ( int idx = 0 ; idx < Jx.size() ; idx++ ) {
				uint i = Jxi[idx];
				std::vector<uint> js = Jxj[idx];
				// ------------------------------------------------------------
				// Partial derivatives of real power flow measurements
				// ------------------------------------------------------------
				if ( tJx[idx] == dPijdVi ) {
					uint j = js[0];
					double Tij = xT[i] - xT[j];
					double gij = std::real(-1.0*Ym[i][j]);
					double bij = std::imag(-1.0*Ym[i][j]);
					Jx[idx] =  -1.0*xV[j] * ( gij*cos(Tij) + bij*sin(Tij) ) + 2*gij*xV[i];
				}
				else if ( tJx[idx] == dPijdVj ) {
					uint j = js[0];
					double Tij = xT[i] - xT[j];
					double gij = std::real(-1.0*Ym[i][j]);
					double bij = std::imag(-1.0*Ym[i][j]);
					Jx[idx] = -1.0*xV[i] * ( gij*cos(Tij) + bij*sin(Tij) );
				}
				else if ( tJx[idx] == dPijdTi ) {
					uint j = js[0];
					double Tij = xT[i] - xT[j];
					double gij = std::real(-1.0*Ym[i][j]);
					double bij = std::imag(-1.0*Ym[i][j]);
					Jx[idx] = xV[i]*xV[j] * ( gij*sin(Tij) - bij*cos(Tij) );
				}
				else if ( tJx[idx] == dPijdTj ) {
					uint j = js[0];
					double Tij = xT[i] - xT[j];
					double gij = std::real(-1.0*Ym[i][j]);
					double bij = std::imag(-1.0*Ym[i][j]);
					Jx[idx] = -1.0*xV[i]*xV[j] * ( gij*sin(Tij) - bij*cos(Tij) );
				}
				// ------------------------------------------------------------
				// Partial derivatives of reactive power flow measurements
				// ------------------------------------------------------------
				else if ( tJx[idx] == dQijdVi ) {
					uint j = js[0];
					double Tij = xT[i] - xT[j];
					double gij = std::real(-1.0*Ym[i][j]);
					double bij = std::imag(-1.0*Ym[i][j]);
					Jx[idx] = -1.0*xV[j] * ( gij*sin(Tij) - bij*cos(Tij) ) - 2.0*xV[i]*bij;
				}
				else if ( tJx[idx] == dQijdVj ) {
					uint j = js[0];
					double Tij = xT[i] - xT[j];
					double gij = std::real(-1.0*Ym[i][j]);
					double bij = std::imag(-1.0*Ym[i][j]);
					Jx[idx] = -1.0*xV[i] * ( gij*sin(Tij) - bij*cos(Tij) );
				}
				else if ( tJx[idx] == dQijdTi ) {
					uint j = js[0];
					double Tij = xT[i] - xT[j];
					double gij = std::real(-1.0*Ym[i][j]);
					double bij = std::imag(-1.0*Ym[i][j]);
					Jx[idx] = -1.0*xV[i]*xV[j] * ( gij*cos(Tij) + bij*sin(Tij) );
				}
				else if ( tJx[idx] == dQijdTj ) {
					uint j = js[0];
					double Tij = xT[i] - xT[j];
					double gij = std::real(-1.0*Ym[i][j]);
					double bij = std::imag(-1.0*Ym[i][j]);
					Jx[idx] = xV[i]*xV[j] * ( gij*cos(Tij) + bij*sin(Tij) );
				}
				// ------------------------------------------------------------
				// Partial derivatives of real power injection measurements
				// ------------------------------------------------------------
				else if ( tJx[idx] == dPidVi ) {
					double h = 0;
					for ( int jdx = 0 ; jdx < js.size() ; jdx++ ) {
						uint j = js[jdx];
						double Tij = xT[i] - xT[j];
						double Gij = std::real(Ym[i][j]);
						double Bij = std::imag(Ym[i][j]);
						h += xV[j] * ( Gij*cos(Tij) + Bij*sin(Tij) );
						}
					Jx[idx] = h + xV[i]*std::real(Ym[i][i]);
				}
				else if ( tJx[idx] == dPidVj ) {
					uint j = js[0];
					double Tij = xT[i] - xT[j];
					double Gij = std::real(Ym[i][j]);
					double Bij = std::imag(Ym[i][j]);
					Jx[idx] = xV[i] * ( Gij*cos(Tij) + Bij*sin(Tij) );
				}
				else if ( tJx[idx] == dPidTi ) {
					double h = 0;
					for ( int jdx = 0 ; jdx < js.size() ; jdx++ ) {
						uint j = js[jdx];
						double Tij = xT[i] - xT[j];
						double Gij = std::real(Ym[i][j]);
						double Bij = std::imag(Ym[i][j]);
						h += xV[i]*xV[j]*( -1.0*Gij*sin(Tij) + Bij*cos(Tij) );
					}
					Jx[idx] = h - xV[i]*xV[i]*std::imag(Ym[i][i]);
				}
				else if ( tJx[idx] == dPidTj ) {
					uint j = js[0];
					double Tij = xT[i] - xT[j];
					double Gij = std::real(Ym[i][j]);
					double Bij = std::imag(Ym[i][j]);
					Jx[idx] = xV[i]*xV[j] * ( Gij*sin(Tij) - Bij*cos(Tij) );
				}
				// ----------------------------------------------------------------
				// Partial derivatives of reactive power injection measurements
				// ----------------------------------------------------------------
				else if ( tJx[idx] == dQidVi ) {
					double h = 0;
					for ( int jdx = 0 ; jdx < js.size() ; jdx++ ) {
						uint j = js[jdx];
						double Tij = xT[i] - xT[j];
						double Gij = std::real(Ym[i][j]);
						double Bij = std::imag(Ym[i][j]);
						h += xV[j] * ( Gij*sin(Tij) - Bij*cos(Tij) );
					}
					Jx[idx] =  h - xV[i]*std::imag(Ym[i][i]);
				}
				else if ( tJx[idx] == dQidVj ) {
					uint j = js[0];
					double Tij = xT[i] - xT[j];
					double Gij = std::real(Ym[i][j]);
					double Bij = std::imag(Ym[i][j]);
					Jx[idx] = xV[i] * ( Gij*sin(Tij) - Bij*cos(Tij) );
				}
				else if ( tJx[idx] == dQidTi ) {
					double h = 0;
					for ( int jdx = 0 ; jdx < js.size() ; jdx++ ) {
						uint j = js[jdx];
						double Tij = xT[i] - xT[j];
						double Gij = std::real(Ym[i][j]);
						double Bij = std::imag(Ym[i][j]);
						h += xV[i]*xV[j] * ( Gij*cos(Tij) + Bij*sin(Tij) );
					}
					Jx[idx] = h - xV[i]*xV[i]*std::real(Ym[i][i]);
				}
				else if ( tJx[idx] == dQidTj ) {
					uint j = js[0];
					double Tij = xT[i] - xT[j];
					double Gij = std::real(Ym[i][j]);
					double Bij = std::imag(Ym[i][j]);
					Jx[idx] =  xV[i]*xV[j] * ( -1.0*Gij*cos(Tij) - Bij*sin(Tij) );
				}
			}
			
			// ----------------------------------------------------------------
			// Estimate State
			// ----------------------------------------------------------------
			std::cout<<"Estimating state...\n";
		
		
			// ----------------------------------------------------------------
			// Setup variables
			// ----------------------------------------------------------------
			// Some variables are established outside of the loop
			// z
			// Note: to improve efficiency, initialize a csc before loop and
			//		insert new measurements directly into the csc
			cs *zraw = cs_spalloc(0,0,zqty,1,1);
			for ( int ii = 0 ; ii < zqty ; ii++ )
				cs_entry(zraw,ii,0,sense[ii]);
			cs *z = cs_compress(zraw); cs_spfree(zraw);
			
			// h
			// Note: to improve efficiency, initialize a csc before loop and
			//		insert new values computed above directly into the csc
			cs *hraw = cs_spalloc(0,0,zqty,1,1);
			for ( int ii = 0 ; ii < zqty ; ii++ )
				cs_entry(hraw,ii,0,hx[ii]);
			cs *h = cs_compress(hraw); cs_spfree(hraw);
			
			// H
			// Note: to improve efficiency, initialize a csc before loop and
			//		insert new values computed above directly into the csc
			cs *Hraw = cs_spalloc(0,0,xqty*zqty,1,1);
			// for ( int ii = 0 ; ii < Jx.size() ; ii ++
			cs *H = cs_compress(Hraw); cs_spfree(Hraw);
			
			cs_print(H,1);
			
			// ----------------------------------------------------------------
			// Predict Step
			// ----------------------------------------------------------------
			// -- compute x_predict = F*x
			cs *xpre = cs_multiply(F,x);
			// -- compute p_predict = F*P*F'+Q
			cs *P1 = cs_transpose(F,1);
			cs *P2 = cs_multiply(P,P1); cs_spfree(P1);
			cs *P3 = cs_multiply(F,P2); cs_spfree(P2);
			cs *Ppre = cs_add(P3,Q,1,1); cs_spfree(P3);
			// clean up
			// cs_spfree(xc);
			// cs_spfree(Fc);
			// cs_spfree(Qc);
			
			// ----------------------------------------------------------------
			// Update Step
			// ----------------------------------------------------------------
			// -- compute y = H*x_predict + z
			cs *y1 = cs_multiply(H,xpre);
			cs *yupd = cs_add(z,y1,1,-1); cs_spfree(y1);
			// -- compute S = H*P_predict*H' + R
			cs *S1 = cs_transpose(H,1);
			cs *S2 = cs_multiply(Ppre,S1); cs_spfree(S1);
			cs *S3 = cs_multiply(H,S2); cs_spfree(S2);
			cs *Supd = cs_add(R,S3,1,1); cs_spfree(S3);
			// -- compute K = P_predict*H'*S^-1
			cs *K1 = cs_transpose(H,1);
			cs *K2 = cs_multiply(Ppre,K1); cs_spfree(K1);
			// cs *K3 = invertcs(Supd);

			// Initialize klusolve variables
			klu_symbolic *klusym;
			klu_numeric *klunum;
			klu_common klucom;
			if (!klu_defaults(&klucom)) throw "klu_defaults exception";
			klusym = klu_analyze(Supd->m,Supd->p,Supd->i,&klucom);
			if (!klusym) throw "klu_analyze exception";
			klunum = klu_factor(Supd->p,Supd->i,Supd->x,klusym,&klucom);
			if (!klunum) throw "klu_factor exception";
			// Initialize an identiy right-hand side
			double *rhs = new double[zqty*zqty];
			for ( int ii = 0 ; ii < zqty*zqty ; ii++ )
				rhs[ii] = ii/zqty == ii%zqty ? 1 : 0;
			klu_solve(klusym,klunum,Supd->m,Supd->n,rhs,&klucom);
			// Convert the inverted result to cs*
			cs *K3raw = cs_spalloc(0,0,zqty*zqty,1,1);
			for ( int ii = 0 ; ii < zqty ; ii++ )
				for ( int jj = 0 ; jj < zqty ; jj++ )
					if (rhs[ii+zqty*jj])
						cs_entry(K3raw,ii,jj,rhs[ii+zqty*jj]);
			delete rhs;
			cs *K3 = cs_compress(K3raw); cs_spfree(K3raw);
			cs *Kupd = cs_multiply(K2,K3); cs_spfree(K2); cs_free(K3);
			
			
			cs *x1 = cs_multiply(Kupd,yupd);
			cs *xupd = cs_add(xpre,x1,1,1); cs_spfree(x1);
			
			// -- compute P = (K*H+I)*P_predict
			cs *P4 = cs_multiply(Kupd,H);
			cs *P5 = cs_add(eyex,P4,1,-1); cs_spfree(P4);
			cs *Pupd = cs_multiply(P5,Ppre); cs_spfree(P5);
			// Cleanup
			cs_spfree(xpre);
			cs_spfree(Ppre);
			cs_spfree(yupd);
			cs_spfree(Supd);
			cs_spfree(Kupd);
			// cs_spfree(Pupd);
			// cs_spfree(z);
			// cs_spfree(H);
			// cs_spfree(R);
			
			
			// Shift updated variables
			cs_spfree(P); P = Pupd; // delete Pupd; //cs_spfree(Pupd);
			// cs_spfree(yint); y = yupd; // delete yupd; //cs_spfree(yupd);
			
			
			// Compute Full State
			
			
			
			// Publish State
			
			
			
			quit = true;
		}
	}
	catch(const char* err) {
		std::cout<<"in catch block...\n";
		//std::printf("%s",err);
		std::cout << err << std::endl;
	}

	return 0;
}
