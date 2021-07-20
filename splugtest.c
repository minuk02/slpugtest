#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>
#include<Windows.h>
#include<stdbool.h>

typedef struct member
{
    char ID[10];
    char PW[20];
    char name[10];
    struct member* next; // 다음노드의 주소저장 포인터
}member;

member* firstmember = NULL;//첫번째 노드

member* makenode()
{
    member* tmp = (member*)malloc(sizeof(member));
    tmp->next = NULL;
    return tmp;
}


void signup(member** head, char ID[], char PW[], char name[])//회원가입
{
    if (!*head)
    {
        FILE* save = fopen("C:\\test\\IDPW.txt", "at");

        *head = makenode();

        strcpy((*head)->ID, ID);
        strcpy((*head)->PW, PW);
        strcpy((*head)->name, name);

        fprintf(save, "ID:%s ", (*head)->ID);
        fprintf(save, "PW:%s ", (*head)->PW);
        fprintf(save, "이름:%s\n", (*head)->name);

        fclose(save);
        return;
    }
    signup(&(*head)->next, ID, PW, name);
}

int IDcheck(char check_ID[])//아이디 중복 확인
{
    FILE* check = fopen("C:\\test\\IDPW.txt", "r");

    char saveID[40];
    char savePW[40];
    char savename[40];
    char compare_ID[40] = { "ID:" };
    int pass = 0;

    strcat(compare_ID, check_ID);

    if (check == NULL)
    {
        printf("사용가능한 아이디 입니다.\n");
        return pass;
    }

    while (1)
    {
        if (feof(check)) break;

        fscanf(check, "%s %s %s", saveID, savePW, savename);
        saveID[strlen(saveID) + 1] = '\0';

        if (strcmp(saveID, compare_ID) == 0)
        {
            printf("이미 존재하는 아이디 입니다.\n");
            pass++;
            return pass;
        }
    }

    printf("사용가능한 아이디입니다.\n");
    fclose(check);
    return 0;
}


int namecheck(char check_name[])//이름 중복 확인
{
    FILE* check = fopen("C:\\test\\IDPW.txt", "r");
    char saveID[40];
    char savePW[40];
    char savename[40];
    char compare_name[40] = { "이름:" };
    int pass = 0;

    strcat(compare_name, check_name);

    if (check == NULL)
        return pass;

    while (1)
    {
        if (feof(check)) break;

        fscanf(check, "%s %s %s", saveID, savePW, savename);
        savename[strlen(savename) + 1] = '\0';

        if (strcmp(savename, compare_name) == 0)
        {
            printf("이미 가입한 회원입니다.\n");
            printf("메뉴로 돌아갑니다.\n");
            pass++;
            Sleep(2000);
            system("cls");
            return pass;
        }
    }
    fclose(check);
    return 0;
}

bool logincheck = 0; // 0 : 비로그인, 1 : 로그인
void login(char login_ID[], char login_PW[]) // 로그인
{
    FILE* check = fopen("C:\\test\\IDPW.txt", "r");

    char compare_ID[30] = { "ID:" };
    char compare_PW[40] = { "PW:" };
    char saveID[20];
    char savePW[30];

    strcat(compare_ID, login_ID);
    strcat(compare_PW, login_PW);

    if (logincheck == true) printf("이미 로그인 되어있습니다.\n");

    while (1)
    {
        if (feof(check)) break;

        fscanf(check, "%s %s", saveID, savePW);
        saveID[strlen(saveID) + 1] = '\0';
        savePW[strlen(savePW) + 1] = '\0';

        if ((strcmp(saveID, compare_ID) == 0) && (strcmp(savePW, compare_PW) == 0))
        {
            logincheck = true;
            break;
        }
        else
        {
            printf("잘못된 아이디이거나 틀린 비밀번호입니다.\n");
            printf("처음화면으로 돌아갑니다.\n");
            Sleep(1000);
            system("cls");
            break;
        }
    }

}

void logout()// 로그아웃
{
    if (logincheck == false)
    {
        printf("로그인 되지 않았습니다. 다시 시도하세요.\n");
        Sleep(700);
        system("cls");
    }
    else
    {
        printf("정말 로그아웃 하시겠습니끼? [y/n]: ");
        char logoutcheck;
        scanf(" %c", &logoutcheck);

        if (logoutcheck == 'y')
        {
            logincheck = false;
            system("cls");
        }
        else if (logoutcheck == 'n')
            return;
    }
}

//void wordquiz(); // 영어단어 맞추기
void withdrawal(char ID[])// 회원탈퇴
{
    int i;
    member* temp;
    member* prev = NULL;

    temp = firstmember;
    if ((strcmp(temp->ID, ID) == 0))
    {
        firstmember = temp->next;
        free(temp);

    }
    else
    {
        for (i = 0; strcmp(temp->ID, ID) != 0; ++i)
        {
            temp = temp->next;
            if (i != 0)
            {
                prev = prev->next;
            }
            else if (i == 1)
            {
                prev = firstmember;
            }
        }
        prev->next = temp->next;
        free(temp);
        return;
    }
}

void Exit()//종료전에 메로리 해제
{
    if (firstmember != NULL)
    {
        while (firstmember->next != NULL)
        {
            member* al = firstmember;
            firstmember = firstmember->next;
        }
        free(firstmember);
    }
}

int main()
{

    int option = 0; //메뉴선택 
    char input_name[8];
    char input_ID[10];
    char input_PW[20];

    char login_ID[10];
    char login_PW[20];

    while (1)
    {
        if (logincheck == true)
        {
            system("cls");
            printf("==================================\n");
            printf("=========== 2021 SPLUG ===========\n");
            printf("======================== %-10s\n", login_ID);
            printf("==================================\n");
            printf("=              메뉴              =\n");
            printf("==================================\n");
            printf("        1. 회원가입\n");
            printf("        2. 로그인\n");
            printf("        3. 로그아웃\n");
            printf("        4. 영어 단어 맞추기\n");
            printf("        5. 회원 탈퇴\n");
            printf("        6. 프로그램 종료\n");
            printf("==================================\n");
            printf("-\n");
            printf("-");
        }
        else
        {
            printf("==================================\n");
            printf("=========== 2021 SPLUG ===========\n");
            printf("==================================\n");
            printf("==================================\n");
            printf("=              메뉴              =\n");
            printf("==================================\n");
            printf("        1. 회원가입\n");
            printf("        2. 로그인\n");
            printf("        3. 로그아웃\n");
            printf("        4. 영어 단어 맞추기\n");
            printf("        5. 회원 탈퇴\n");
            printf("        6. 프로그램 종료\n");
            printf("==================================\n");
            printf("-\n");
            printf("-");
        }
        scanf("%d", &option);

        int cnt = 1;
        switch (option)
        {
        case 1: //회원가입
            system("cls");
            printf("회원가입 페이지\n");

            while (1)
            {

                int result_ID = 0;
                printf("ID : ");
                scanf("%s", input_ID);

                result_ID = IDcheck(input_ID);
                if (result_ID == 0)
                    break;
            }
            printf("PW : ");
            scanf("%s", input_PW);

            printf("이름 : ");
            scanf("%s", input_name);
            {
                int result_name = 0;
                result_name = namecheck(input_name);
                if (result_name != 0)
                    continue;
                else
                    signup(&firstmember, input_ID, input_PW, input_name); // 회원가입 정보 저장
            }

            system("cls");
            break;
        case 2:
            system("cls");

            if (logincheck == true)
            {
                printf("이미 로그인하셨습니다.\n");
                Sleep(700);
                continue;
            }

            printf("로그인\n");
            printf("ID : ");
            scanf("%s", login_ID);

            printf("PW : ");
            scanf("%s", login_PW);

            login(login_ID, login_PW);

            break;
        case 3:
            logout();
            break;
        case 4:
            //wordquiz();
            break;
        case 5:
            if (logincheck == false)
            {
                printf("로그인 상태가 아닙니다.\n");
                Sleep(700);
                system("cls");
                continue;
            }
            withdrawal(login_ID);
            break;
        case 6:
            Exit();
            exit(0);
            break;
        default:
            printf("메뉴에 없습니다악!!!!!!!\n");
            Sleep(700);
            system("cls");
            break;
        }
    }

    return 0;
}
