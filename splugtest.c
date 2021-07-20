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
    struct member* next; // ��������� �ּ����� ������
}member;

member* firstmember = NULL;//ù��° ���

member* makenode()
{
    member* tmp = (member*)malloc(sizeof(member));
    tmp->next = NULL;
    return tmp;
}


void signup(member** head, char ID[], char PW[], char name[])//ȸ������
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
        fprintf(save, "�̸�:%s\n", (*head)->name);

        fclose(save);
        return;
    }
    signup(&(*head)->next, ID, PW, name);
}

int IDcheck(char check_ID[])//���̵� �ߺ� Ȯ��
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
        printf("��밡���� ���̵� �Դϴ�.\n");
        return pass;
    }

    while (1)
    {
        if (feof(check)) break;

        fscanf(check, "%s %s %s", saveID, savePW, savename);
        saveID[strlen(saveID) + 1] = '\0';

        if (strcmp(saveID, compare_ID) == 0)
        {
            printf("�̹� �����ϴ� ���̵� �Դϴ�.\n");
            pass++;
            return pass;
        }
    }

    printf("��밡���� ���̵��Դϴ�.\n");
    fclose(check);
    return 0;
}


int namecheck(char check_name[])//�̸� �ߺ� Ȯ��
{
    FILE* check = fopen("C:\\test\\IDPW.txt", "r");
    char saveID[40];
    char savePW[40];
    char savename[40];
    char compare_name[40] = { "�̸�:" };
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
            printf("�̹� ������ ȸ���Դϴ�.\n");
            printf("�޴��� ���ư��ϴ�.\n");
            pass++;
            Sleep(2000);
            system("cls");
            return pass;
        }
    }
    fclose(check);
    return 0;
}

bool logincheck = 0; // 0 : ��α���, 1 : �α���
void login(char login_ID[], char login_PW[]) // �α���
{
    FILE* check = fopen("C:\\test\\IDPW.txt", "r");

    char compare_ID[30] = { "ID:" };
    char compare_PW[40] = { "PW:" };
    char saveID[20];
    char savePW[30];

    strcat(compare_ID, login_ID);
    strcat(compare_PW, login_PW);

    if (logincheck == true) printf("�̹� �α��� �Ǿ��ֽ��ϴ�.\n");

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
            printf("�߸��� ���̵��̰ų� Ʋ�� ��й�ȣ�Դϴ�.\n");
            printf("ó��ȭ������ ���ư��ϴ�.\n");
            Sleep(1000);
            system("cls");
            break;
        }
    }

}

void logout()// �α׾ƿ�
{
    if (logincheck == false)
    {
        printf("�α��� ���� �ʾҽ��ϴ�. �ٽ� �õ��ϼ���.\n");
        Sleep(700);
        system("cls");
    }
    else
    {
        printf("���� �α׾ƿ� �Ͻðڽ��ϳ�? [y/n]: ");
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

//void wordquiz(); // ����ܾ� ���߱�
void withdrawal(char ID[])// ȸ��Ż��
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

void Exit()//�������� �޷θ� ����
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

    int option = 0; //�޴����� 
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
            printf("=              �޴�              =\n");
            printf("==================================\n");
            printf("        1. ȸ������\n");
            printf("        2. �α���\n");
            printf("        3. �α׾ƿ�\n");
            printf("        4. ���� �ܾ� ���߱�\n");
            printf("        5. ȸ�� Ż��\n");
            printf("        6. ���α׷� ����\n");
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
            printf("=              �޴�              =\n");
            printf("==================================\n");
            printf("        1. ȸ������\n");
            printf("        2. �α���\n");
            printf("        3. �α׾ƿ�\n");
            printf("        4. ���� �ܾ� ���߱�\n");
            printf("        5. ȸ�� Ż��\n");
            printf("        6. ���α׷� ����\n");
            printf("==================================\n");
            printf("-\n");
            printf("-");
        }
        scanf("%d", &option);

        int cnt = 1;
        switch (option)
        {
        case 1: //ȸ������
            system("cls");
            printf("ȸ������ ������\n");

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

            printf("�̸� : ");
            scanf("%s", input_name);
            {
                int result_name = 0;
                result_name = namecheck(input_name);
                if (result_name != 0)
                    continue;
                else
                    signup(&firstmember, input_ID, input_PW, input_name); // ȸ������ ���� ����
            }

            system("cls");
            break;
        case 2:
            system("cls");

            if (logincheck == true)
            {
                printf("�̹� �α����ϼ̽��ϴ�.\n");
                Sleep(700);
                continue;
            }

            printf("�α���\n");
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
                printf("�α��� ���°� �ƴմϴ�.\n");
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
            printf("�޴��� �����ϴپ�!!!!!!!\n");
            Sleep(700);
            system("cls");
            break;
        }
    }

    return 0;
}
