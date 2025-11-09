#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

struct Farmer {
    char name[20];
    char soil[20];
    char season[20];
};

void advice(FILE *p, char soil[], char season[]);
void irrigation(FILE *p, char soil[], char season[]);
void addFarmer();
void viewFarmers();
void updateFarmer();
void deleteFarmer();
void generateAdvice();

int main() {
    int choice;
    do {
        printf("\n===== SMART FARM ADVISOR MENU =====\n");
        printf("1. Add Farmer\n");
        printf("2. View Farmers\n");
        printf("3. Update Farmer\n");
        printf("4. Delete Farmer\n");
        printf("5. Generate Advice for All Farmers\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: addFarmer(); break;
            case 2: viewFarmers(); break;
            case 3: updateFarmer(); break;
            case 4: deleteFarmer(); break;
            case 5: generateAdvice(); break;         
	    case 6: printf("Exiting program...\n"); break;
            default: printf("Invalid choice. Try again!\n");
        }
    } while(choice != 6);

    return 0;
}

//================ ADD FARMER ===================
void addFarmer() {
    FILE *fp;
    struct Farmer f;
    fp = fopen("farmer_data.txt", "a");
    if(fp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    printf("\nEnter farmer name: ");
    scanf(" %[^\n]", f.name);
    printf("Enter soil type:(red/black/alluvial/laterite/arid/mountain) ");
    scanf(" %s", f.soil);
    printf("Enter season:(kharif/rabi/zaid) ");
    scanf(" %s", f.season);

    fprintf(fp, "%s %s %s\n", f.name, f.soil, f.season);
    fclose(fp);
    printf("✅ Farmer added successfully!\n");
}

//================ VIEW FARMERS ===================
void viewFarmers() {
    FILE *fp;
    struct Farmer f;
    fp = fopen("farmer_data.txt", "r");
    if(fp == NULL) {
        printf("No records found.\n");
        return;
    }

    printf("\n--- Farmer Records ---\n");
    while(fscanf(fp, "%s %s %s", f.name, f.soil, f.season) == 3) {
        printf("Name: %s | Soil: %s | Season: %s\n", f.name, f.soil, f.season);
    }
    fclose(fp);
}

//================ UPDATE FARMER ===================
void updateFarmer() {
    FILE *fp, *temp;
    struct Farmer f;
    char name[20];
    int found = 0;

    fp = fopen("farmer_data.txt", "r");
    temp = fopen("temp.txt", "w");

    if(fp == NULL || temp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    printf("Enter farmer name to update: ");
    scanf(" %s", name);

    while(fscanf(fp, "%s %s %s", f.name, f.soil, f.season) == 3) {
        if(strcmp(f.name, name) == 0) {
            found = 1;
            printf("Enter new soil: ");
            scanf(" %s", f.soil);
            printf("Enter new season: ");
            scanf(" %s", f.season);
        }
        fprintf(temp, "%s %s %s\n", f.name, f.soil, f.season);
    }

    fclose(fp);
    fclose(temp);

    remove("farmer_data.txt");
    rename("temp.txt", "farmer_data.txt");

    if(found)
        printf("✅ Farmer updated successfully!\n");
    else
        printf("Farmer not found.\n");
}

//================ DELETE FARMER ===================
void deleteFarmer() {
    FILE *fp, *temp;
    struct Farmer f;
    char name[20];
    int found = 0;

    fp = fopen("farmer_data.txt", "r");
    temp = fopen("temp.txt", "w");

    if(fp == NULL || temp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    printf("Enter farmer name to delete: ");
    scanf(" %s", name);

    while(fscanf(fp, "%s %s %s", f.name, f.soil, f.season) == 3) {
        if(strcmp(f.name, name) != 0) {
            fprintf(temp, "%s %s %s\n", f.name, f.soil, f.season);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    remove("farmer_data.txt");
    rename("temp.txt", "farmer_data.txt");

    if(found)
        printf("✅ Farmer deleted successfully!\n");
    else
        printf("Farmer not found.\n");
}

//================ GENERATE ADVICE ===================
void generateAdvice() {
    FILE *fp, *p;
    struct Farmer f;
    char name[20];
    int found = 0;

    fp = fopen("farmer_data.txt", "r");
    p = fopen("Farmer_Advice.txt", "w");

    if(fp == NULL) {
        printf("No farmer data found.\n");
        return;
    }
    if(p == NULL) {
        printf("Error creating advice file.\n");
        fclose(fp);
        return;
    }

    printf("Enter farmer name to generate advice: ");
    scanf(" %[^\n]", name);

    while(fscanf(fp, "%s %s %s", f.name, f.soil, f.season) == 3) {
        if(strcmp(f.name, name) == 0) {
            found = 1;
            fprintf(p, "Farmer Name: %s\n", f.name);
            fprintf(p, "Soil Type: %s\n", f.soil);
            fprintf(p, "Season: %s\n", f.season);
            advice(p, f.soil, f.season);
            irrigation(p, f.soil, f.season);
            fprintf(p, "----------------------------------------\n\n");
            break;
        }
    }

    fclose(fp);
    fclose(p);

    if(found)
        printf("Advice generated successfully in Farmer_Advice.txt\n");
    else
        printf("Farmer not found.\n");
}

void advice(FILE *p,char soil[], char season[]) {
    // Convert to lowercase for easy comparison
    for (int i = 0; soil[i]; i++) soil[i] = tolower(soil[i]);
    for (int i = 0; season[i]; i++) season[i] = tolower(season[i]);

    // RED SOIL
    if (strcmp(soil, "red") == 0 && strcmp(season, "kharif") == 0){
        printf("Suggested crops: Cotton, Millets\nFertilizer: Urea\n");
	fprintf(p,"Suggested crops: Cotton, Millets\nFertilizer: Urea\n");
	}
    else if (strcmp(soil, "red") == 0 && strcmp(season, "rabi") == 0){
        printf("Suggested crops: Groundnut, Pulses\nFertilizer: DAP\n");
	fprintf(p,"Suggested crops: Groundnut, Pulses\nFertilizer: DAP\n");
	}
    else if (strcmp(soil, "red") == 0 && strcmp(season, "zaid") == 0){
        printf("Suggested crops: Vegetables, Maize\nFertilizer: NPK\n");
	fprintf(p,"Suggested crops: Vegetables, Maize\nFertilizer: NPK\n");
	}	

    // BLACK SOIL
    else if (strcmp(soil, "black") == 0 && strcmp(season, "kharif") == 0){
        printf("Suggested crops: Cotton, Soybean\nFertilizer: Ammonium Sulphate\n");
	fprintf(p,"Suggested crops: Cotton, Soybean\nFertilizer: Ammonium Sulphate\n");
	}
    else if (strcmp(soil, "black") == 0 && strcmp(season, "rabi") == 0){
        printf("Suggested crops: Wheat, Gram\nFertilizer: Urea\n");
	fprintf(p,"Suggested crops: Wheat, Gram\nFertilizer: Urea\n");
	}
    else if (strcmp(soil, "black") == 0 && strcmp(season, "zaid") == 0){
        printf("Suggested crops: Maize, Vegetables\nFertilizer: NPK\n");
	fprintf(p,"Suggested crops: Maize, Vegetables\nFertilizer: NPK\n");
	}

    // ALLUVIAL SOIL
    else if (strcmp(soil, "alluvial") == 0 && strcmp(season, "kharif") == 0){
        printf("Suggested crops: Rice, Sugarcane\nFertilizer: DAP\n");
	fprintf(p,"Suggested crops: Rice, Sugarcane\nFertilizer: DAP\n");
	}
    else if (strcmp(soil, "alluvial") == 0 && strcmp(season, "rabi") == 0){
        printf("Suggested crops: Wheat, Barley\nFertilizer: NPK\n");
	fprintf(p,"Suggested crops: Wheat, Barley\nFertilizer: NPK\n");
	}
    else if (strcmp(soil, "alluvial") == 0 && strcmp(season, "zaid") == 0){
        printf("Suggested crops: Fruits, Vegetables\nFertilizer: Compost\n");
	fprintf(p,"Suggested crops: Fruits, Vegetables\nFertilizer: Compost\n");
	}

    // LATERITE SOIL
    else if (strcmp(soil, "laterite") == 0 && strcmp(season, "kharif") == 0){
        printf("Suggested crops: Tea, Coffee\nFertilizer: Organic Manure\n");
	fprintf(p,"Suggested crops: Tea, Coffee\nFertilizer: Organic Manure\n");
	}
    else if (strcmp(soil, "laterite") == 0 && strcmp(season, "rabi") == 0){
        printf("Suggested crops: Cashew, Coconut\nFertilizer: Compost\n");
	fprintf(p,"Suggested crops: Cashew, Coconut\nFertilizer: Compost\n");
	}
    else if (strcmp(soil, "laterite") == 0 && strcmp(season, "zaid") == 0){
        printf("Suggested crops: Pineapple, Banana\nFertilizer: NPK\n");
	fprintf(p,"Suggested crops: Pineapple, Banana\nFertilizer: NPK\n");
	}

    // ARID SOIL
    else if (strcmp(soil, "arid") == 0 && strcmp(season, "kharif") == 0){
        printf("Suggested crops: Bajra, Jowar\nFertilizer: Urea\n");
	fprintf(p,"Suggested crops: Bajra, Jowar\nFertilizer: Urea\n");
	}
    else if (strcmp(soil, "arid") == 0 && strcmp(season, "rabi") == 0){
        printf("Suggested crops: Pulses, Gram\nFertilizer: DAP\n");
	fprintf(p,"Suggested crops: Pulses, Gram\nFertilizer: DAP\n");
	}
    else if (strcmp(soil, "arid") == 0 && strcmp(season, "zaid") == 0){
        printf("Suggested crops: Cumin, Watermelon\nFertilizer: NPK\n");
	fprintf(p,"Suggested crops: Cumin, Watermelon\nFertilizer: NPK\n");
	}

    // MOUNTAIN SOIL
    else if (strcmp(soil, "mountain") == 0 && strcmp(season, "kharif") == 0){
        printf("Suggested crops: Tea, Maize\nFertilizer: Organic Manure\n");
	fprintf(p,"Suggested crops: Tea, Maize\nFertilizer: Organic Manure\n");
	}
    else if (strcmp(soil, "mountain") == 0 && strcmp(season, "rabi") == 0){
        printf("Suggested crops: Apple, Barley\nFertilizer: Compost\n");
	fprintf(p,"Suggested crops: Apple, Barley\nFertilizer: Compost\n");
	}
    else if (strcmp(soil, "mountain") == 0 && strcmp(season, "zaid") == 0){
        printf("Suggested crops: Fruits, Vegetables\nFertilizer: NPK Mix\n");
	fprintf(p,"Suggested crops: Fruits, Vegetables\nFertilizer: NPK Mix\n");
	}

    // INVALID COMBINATION
    else{
        printf("We don’t have data for this soil and season combination.\nPlease consult an agriculture specialist.\n");
	fprintf(p,"We don’t have data for this soil and season combination.\nPlease consult an agriculture specialist.\n");
	}
}
void irrigation(FILE *p,char soil[],char season[]){
	for(int i=0;soil[i];i++){
		soil[i]=tolower(soil[i]);
	}
	for(int i=0;season[i];i++){
		season[i]=tolower(season[i]);
	}	
	int soiltype=0;
	if(strcmp(soil,"red")==0){
		soiltype=1;
	}
	else if(strcmp(soil,"black")==0){
		soiltype=2;
	}
	else if(strcmp(soil,"alluvial")==0){
		soiltype=3;
	}
	else if(strcmp(soil,"laterite")==0){
		soiltype=4;
	}
	else if(strcmp(soil,"arid")==0){
		soiltype=5;
	}
	else if(strcmp(soil,"mountain")==0){
		soiltype=6;
	}
	printf("\nSuggetion to irrigate field:");
	fprintf(p,"\nSuggetion to irrigate field :");
	switch(soiltype){
		case 1:
			if(strcmp(season,"kharif")==0){
				printf("\n Low rainfall:Irrigate 4-5 times\n High rainfall:Irrigate 2 times\n");
				
				fprintf(p,"\n Low rainfall:Irrigate 4-5 times\n High rainfall:Irrigate 2 times\n");
			}
			else if(strcmp(season,"rabi")==0){
				printf("\n Low rainfall:Irrigate 5 times\n High rainfall:Irrigate 2-3 times\n");
				
				fprintf(p,"\n Low rainfall:Irrigate 5 times\n High rainfall:Irrigate 2-3 times\n");
			}
			else if(strcmp(season,"zaid")==0){
				printf("\n Low rainfall:Irrigate 6-7 times\n High rainfall:Irrigate 3 times\n");
								
				fprintf(p,"\n Low rainfall:Irrigate 6-7 times\n High rainfall:Irrigate 3 times\n");
			}
			break;
		case 2:
			if(strcmp(season,"kharif")==0){
				printf("\n Low rainfall:Irrigate 3-4 times\n High rainfall:Irrigate 1-2 times\n");
				
				fprintf(p,"\n Low rainfall:Irrigate 3-4 times\n High rainfall:Irrigate 1-2 times\n");
			}
			else if(strcmp(season,"rabi")==0){
				printf("\n Low rainfall:Irrigate 4 times\n High rainfall:Irrigate 2 times\n");
				
				fprintf(p,"\n Low rainfall:Irrigate 4 times\n High rainfall:Irrigate 2 times\n");
			}
			else if(strcmp(season,"zaid")==0){
				printf("\n Low rainfall:Irrigate 5 times\n High rainfall:Irrigate 3 times\n");
				
				fprintf(p,"\n Low rainfall:Irrigate 5 times\n High rainfall:Irrigate 3 times\n");
			}
			break;
		case 3:
			if(strcmp(season,"kharif")==0){
				printf("\n Low rainfall:Irrigate 6-8 times\n High rainfall:Irrigate 3-4 times\n");
				
				fprintf(p,"\n Low rainfall:Irrigate 6-8 times\n High rainfall:Irrigate 3-4 times\n");
			}
			else if(strcmp(season,"rabi")==0){
				printf("\n Low rainfall:Irrigate 5 times\n High rainfall:Irrigate 2-3 times\n");
				
				fprintf(p,"\n Low rainfall:Irrigate 5 times\n High rainfall:Irrigate 2-3 times\n");
			}
			else if(strcmp(season,"zaid")==0){
				printf("\n Low rainfall:Irrigate 6-7 times\n High rainfall:Irrigate 3 times\n");
				
				fprintf(p,"\n Low rainfall:Irrigate 6-7 times\n High rainfall:Irrigate 3 times\n");
			}
			break;
		case 4:
			if(strcmp(season,"kharif")==0){
				printf("\n Low rainfall:Irrigate 5-6 times\n High rainfall:Irrigate 3 times\n");
				
				fprintf(p,"\n Low rainfall:Irrigate 5-6 times\n High rainfall:Irrigate 3 times\n");
			}
			else if(strcmp(season,"rabi")==0){
				printf("\n Low rainfall:Irrigate 4 times\n High rainfall:Irrigate 2 times\n");
				
				fprintf(p,"\n Low rainfall:Irrigate 4 times\n High rainfall:Irrigate 2 times\n");
			}
			else if(strcmp(season,"zaid")==0){
				printf("\n Low rainfall:Irrigate 7 times\n High rainfall:Irrigate 3-4 times\n");
				
				fprintf(p,"\n Low rainfall:Irrigate 7 times\n High rainfall:Irrigate 3-4 times\n");
			}
			break;
		case 5:
			if(strcmp(season,"kharif")==0){
				printf("\n Low rainfall:Irrigate 6 times\n High rainfall:Irrigate 3 times\n");
			
				fprintf(p,"\n Low rainfall:Irrigate 6 times\n High rainfall:Irrigate 3 times\n");
			}
			else if(strcmp(season,"rabi")==0){
				printf("\n Low rainfall:Irrigate 5 times\n High rainfall:Irrigate 2-3 times\n");
				
				fprintf(p,"\n Low rainfall:Irrigate 5 times\n High rainfall:Irrigate 2-3 times\n");
			}
			else if(strcmp(season,"zaid")==0){
				printf("\n Low rainfall:Irrigate 7-8 times\n High rainfall:Irrigate 4 times\n");
				
				fprintf(p,"\n Low rainfall:Irrigate 7-8 times\n High rainfall:Irrigate 4 times\n");
			}
			break;
		case 6:
			if(strcmp(season,"kharif")==0){
				printf("\n Low rainfall:Irrigate 4-5 times\n High rainfall:Irrigate 2 times\n");

				fprintf(p,"\n Low rainfall:Irrigate 4-5 times\n High rainfall:Irrigate 2 times\n");
			}
			else if(strcmp(season,"rabi")==0){
				printf("\n Low rainfall:Irrigate 3-4 times\n High rainfall:Irrigate 2 times\n");
		
				fprintf(p,"\n Low rainfall:Irrigate 3-4 times\n High raifall:Irrigate 2 times\n");
			}
			else if(strcmp(season,"zaid")==0){
				printf("\n Low rainfall:Irrigate 5-6 times\n High rainfall:Irrigate 3 times\n");
				
				fprintf(p,"\n Low rainfall:Irrigate 5-6 times\n High rainfall:Irrigate 3 times\n");
			}
			break;
		default:
			printf("\nNo soil type avialable");

			fprintf(p,"\nNo soil type avialable");
	}
}