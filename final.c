#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define MAX 10 
typedef struct {
char name[30];
char team[30];
int value; 
} Player;
Player players[MAX] = {
{"조현우", "울산 현대", 10}, {"김영권", "울산 현대", 7}, {"홍철", "강원 FC", 5}, {"주민규", "대전 하나", 9}, {"이승우", "전북 현대", 15}, {"린가드", "FC 서울", 20}, {"이동경", "김천 상무", 10}, {"전진우", "전북 현대", 9}, {"송민규", "전북 현대", 8}, {"세징야", "대구 FC", 7}
};
int squadSize = 0; 
int budget = 50; 
int currentMonth = 1; 
int currentYear = 2025; 
int transferWindowOpen = 0; 
int targetTotalValue = 100; 
void showAllPlayers() {
printf("\n[선수 목록] (예산: %d억)\n", budget);
printf("\n[내 팀 선수]\n");
int foundMyTeam = 0;
for (int i = 0; i < MAX; i++) {
if (strcmp(players[i].team, "MyTeam") == 0) { 
foundMyTeam = 1;
printf("%d. %s | 소속: %s | 가치: %d억\n",
i + 1, players[i].name, players[i].team, players[i].value);
}
}
if (!foundMyTeam) {
printf(">> 내 팀에 선수가 없습니다.\n");
}
printf("\n[다른 팀 선수]\n");
int foundOtherTeam = 0;
for (int i = 0; i < MAX; i++) {
if (strcmp(players[i].team, "MyTeam") != 0) { 
foundOtherTeam = 1;
printf("%d. %s | 소속: %s | 가치: %d억\n",
i + 1, players[i].name, players[i].team, players[i].value);
}
}
if (!foundOtherTeam) {
printf(">> 다른 팀 선수가 없습니다.\n");
}
}
void transferPlayer() {
if (transferWindowOpen == 0) {
printf(">> 이적시장이 열려 있지 않습니다. 6개월마다 이적시장이 열립니다.\n");
return;
}
char name[30];
printf("영입할 선수 이름: ");
scanf(" %[^\n]", name);
for (int i = 0; i < MAX; i++) {
if (strcmp(players[i].name, name) == 0 && strcmp(players[i].team, "MyTeam") != 0) {
if (budget < players[i].value) {
printf(">> 예산이 부족합니다! 현재 예산: %d억\n", budget);
return;
}
budget -= players[i].value;
strcpy(players[i].team, "MyTeam");
printf(">> 영입 성공! 남은 예산: %d억\n", budget);
return;
}
}
printf(">> 선수를 찾을 수 없습니다.\n");
}
void updatePlayerValues() {
for (int i = 0; i < MAX; i++) {
int valueChange = (rand() % 7) - 3;
players[i].value += valueChange;
if (players[i].value < 1) players[i].value = 1; 
if (players[i].value > 30) players[i].value = 30; 
}
}
void advanceTime() {
currentMonth += 2;
if (currentMonth > 12) {
currentMonth = 1;
currentYear++;
}
printf("\n현재 날짜: %d/%02d\n", currentYear, currentMonth);
updatePlayerValues();
if (currentMonth == 7 || currentMonth == 1) {
transferWindowOpen = 1; 
printf("이적시장이 열렸습니다! 선수를 영입할 수 있습니다.\n");
} else {
transferWindowOpen = 0; 
}
}
void checkMarketOpen() {
if (transferWindowOpen) {
printf("이적시장이 열려 있습니다. 선수를 영입할 수 있습니다.\n");
} else {
printf("이적시장이 닫혀 있습니다. 6개월마다 열립니다.\n");
}
}
void tradePlayer() {
if (transferWindowOpen == 1) {
printf(">> 이적시장이 열려 있으므로 트레이드는 불가능합니다. 영입만 가능합니다.\n");
return; 
}
char player1Name[30], player2Name[30];
int player1Index = -1, player2Index = -1;
printf("\n[트레이드] 두 선수를 선택하여 트레이드를 진행하세요.\n");
printf("트레이드할 첫 번째 선수 이름: ");
scanf(" %[^\n]", player1Name);
printf("트레이드할 두 번째 선수 이름: ");
scanf(" %[^\n]", player2Name);
for (int i = 0; i < MAX; i++) {
if (strcmp(players[i].name, player1Name) == 0) {
player1Index = i;
}
if (strcmp(players[i].name, player2Name) == 0) {
player2Index = i;
}
}
if (player1Index == -1 || player2Index == -1) {
printf(">> 선수를 찾을 수 없습니다.\n");
return;
}
if (abs(players[player1Index].value - players[player2Index].value) <= 3) {
char tempTeam[30];
strcpy(tempTeam, players[player1Index].team);
strcpy(players[player1Index].team, players[player2Index].team);
strcpy(players[player2Index].team, tempTeam);
printf(">> 트레이드 완료! %s와 %s가 팀을 교환했습니다.\n", players[player1Index].name, players[player2Index].name);
} else {
printf(">> 트레이드 실패! 두 선수의 가치 차이가 너무 큽니다.\n");
}
}
int checkGameEnd() {
for (int i = 0; i < MAX; i++) {
if (strcmp(players[i].team, "MyTeam") != 0) {
return 0; 
}
}
return 1; 
}
int main() {
srand(time(NULL)); 
int choice;
while (1) {
printf("\n===== 이적시장 시뮬레이터 =====\n");
printf("1. 선수 목록 보기 (내 팀과 예산)\n");
printf("2. 선수 영입 시도\n");
printf("3. 시간 흐르기 (2개월 진행)\n");
printf("4. 트레이드 진행\n");
printf("5. 종료\n");
printf(">> 선택: ");
scanf("%d", &choice);
switch (choice) {
case 1: showAllPlayers(); break;
case 2: transferPlayer(); break;
case 3: advanceTime(); checkMarketOpen(); break;
case 4: tradePlayer(); break;
case 5: printf("프로그램을 종료합니다.\n"); return 0;
default: printf(">> 잘못된 입력입니다.\n");
}
if (checkGameEnd()) {
printf("\n축하합니다! 모든 선수를 영입하여 목표를 달성했습니다! 현재 날짜: %d/%02d\n", currentYear, currentMonth);
break;
}
}
return 0;
}

