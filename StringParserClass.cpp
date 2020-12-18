/*
 * StringParserClass.cpp
 *
 *  Created on: Oct 8, 2017
 *      Author: keith
 */

#include <string>
#include <string.h>
#include "../327_proj3_test/includes/StringParserClass.h"
#include "../327_proj3_test/includes/constants.h"
using namespace std;


namespace KP_StringParserClass{

		//dont forget to initialize member variables
		StringParserClass::StringParserClass(void):pStartTag(0), pEndTag(0), areTagsSet(false){
		}

		//call cleanup to release any allocated memory
		StringParserClass::~StringParserClass(void){
			cleanup();
		}

		//these are the start tag and the end tags that we want to find,
		//presumably the data of interest is between them, please make a
		//COPY of what pStartTag and pEndTag point to.  In other words
		//DO NOT SET pStartTag = pStart
		//returns:
		//SUCCESS
		//ERROR_TAGS_NULL if either pStart or pEnd is null
		int StringParserClass::setTags(const char *pStart, const char *pEnd) {
			if (pStart == NULL|| pEnd == NULL){
				return ERROR_TAGS_NULL;
			}
			cleanup();

			int startlen = strlen(pStart);
			int endlen = strlen(pEnd);

			pStartTag = new char[startlen + 1];
			pEndTag = new char[endlen + 1];

			strcpy(pStartTag, pStart);
			strcpy(pEndTag, pEnd);
			areTagsSet = true;

			return SUCCESS;
		}

		//First clears myVector
		//going to search thru pDataToSearchThru, looking for info bracketed by
		//pStartTag and pEndTag, will add that info only to myVector
		//returns
		//SUCCESS  finished searching for data between tags, results in myVector (0 or more entries)
		//ERROR_TAGS_NULL if either pStart or pEnd is null
		//ERROR_DATA_NULL pDataToSearchThru is null
		int StringParserClass::getDataBetweenTags(char *pDataToSearchThru, vector<string> &myVector){
			myVector.clear();

			if (pStartTag == NULL || pEndTag == NULL){
				return ERROR_TAGS_NULL;
			}

			if (pDataToSearchThru == NULL){
				return ERROR_DATA_NULL;
			}

			int lenDataToSearch = strlen(pDataToSearchThru);
			int lenStartTag = strlen(pStartTag);
			int lenEndTag = strlen(pEndTag);

			char firstStart = pStartTag[0];
			char firstEnd = pEndTag[0];
			string tmp = "";

			for (int i = 0; i < lenDataToSearch; i++){
				char curr = pDataToSearchThru[i];
				char *pCurr = &pDataToSearchThru[i];

				if (curr == firstStart){
					if (strncmp(pCurr, pStartTag, lenStartTag) == 0){
						i += lenStartTag;
						curr = pDataToSearchThru[i];
						while(curr != firstEnd){
							tmp += curr;
							i++;
							curr = pDataToSearchThru[i];
						}

						if (curr == firstEnd){
							pCurr = &pDataToSearchThru[i];
							if (strncmp(pCurr, pEndTag, lenEndTag) == 0){
								myVector.push_back(tmp);
								tmp = "";
							}
						}
					}
				}
			}

			return SUCCESS;
		}


		void StringParserClass::cleanup(){
			if(pStartTag && pEndTag){
				delete [] pStartTag;
				delete [] pEndTag;
			}
			pStartTag = NULL;
			pEndTag = NULL;
		}

		//Searches a string starting at pStart for pTagToLookFor
		//returns:
		//SUCCESS  found pTagToLookFor, pStart points to beginning of tag and pEnd points to end of tag
		//FAIL did not find pTagToLookFor and pEnd points to 0
		//ERROR_TAGS_NULL if either pStart or pEnd is null
		int StringParserClass::findTag(char *pTagToLookFor, char *&pStart, char *&pEnd){
			if (pTagToLookFor == 0 && pEnd == 0){
				return FAIL;
			}

			if (pStart == NULL || pEnd == NULL){
				return ERROR_TAGS_NULL;
			}

			int lenStart = strlen(pStart);
			int lenTag = strlen(pTagToLookFor);

			for (int i = 0; i < lenStart; i++){
				if (*(pStart + i) == pTagToLookFor[0]){
					if (strncmp((pStart + i), pTagToLookFor, lenTag) == 0){
						*pStart = *(pStart + i);
						return SUCCESS;
					}
				}
			}

			return FAIL;
		}
}

