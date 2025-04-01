#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_CLIENTES 100
#define MAX_SERVICOS 10
#define MAX_AGENDAMENTOS 30

typedef struct {
    int id;
    char nome[50];
    char telefone[15];
} Cliente;

typedef struct {
    int id;
    char descricao[50];
    float preco;
    int duracao; // em minutos
} Servico;

typedef struct {
    int id;
    int id_cliente;
    int id_servico;
    char data[11]; // formato DD/MM/AAAA
    char hora[6];  // formato HH:MM
    int realizado;
} Agendamento;

Cliente clientes[MAX_CLIENTES];
Servico servicos[MAX_SERVICOS];
Agendamento agendamentos[MAX_AGENDAMENTOS];

int totalClientes = 0;
int totalServicos = 0;
int totalAgendamentos = 0;

void cadastrarCliente() {
    if (totalClientes >= MAX_CLIENTES) {
        printf("Limite de clientes atingido!\n");
        return;
    }
    
    Cliente novo;
    novo.id = totalClientes + 1;
    
    printf("\n--- Cadastro de Cliente ---\n");
    printf("Nome: ");
    scanf(" %[^\n]", novo.nome);
    printf("Telefone: ");
    scanf(" %s", novo.telefone);
    
    clientes[totalClientes++] = novo;
    printf("Cliente cadastrado com sucesso! ID: %d\n", novo.id);
}

void listarClientes() {
    printf("\n--- Lista de Clientes ---\n");
    for (int i = 0; i < totalClientes; i++) {
        printf("ID: %d | Nome: %s | Telefone: %s\n", 
               clientes[i].id, clientes[i].nome, clientes[i].telefone);
    }
}

void cadastrarServico() {
    if (totalServicos >= MAX_SERVICOS) {
        printf("Limite de serviços atingido!\n");
        return;
    }
    
    Servico novo;
    novo.id = totalServicos + 1;
    
    printf("\n--- Cadastro de Serviço ---\n");
    printf("Descrição: ");
    scanf(" %[^\n]", novo.descricao);
    printf("Preço: ");
    scanf("%f", &novo.preco);
    printf("Duração (minutos): ");
    scanf("%d", &novo.duracao);
    
    servicos[totalServicos++] = novo;
    printf("Serviço cadastrado com sucesso! ID: %d\n", novo.id);
}

void listarServicos() {
    printf("\n--- Lista de Serviços ---\n");
    for (int i = 0; i < totalServicos; i++) {
        printf("ID: %d | %s | R$%.2f | %d min\n", 
               servicos[i].id, servicos[i].descricao, 
               servicos[i].preco, servicos[i].duracao);
    }
}

void agendarServico() {
    if (totalAgendamentos >= MAX_AGENDAMENTOS) {
        printf("Limite de agendamentos atingido!\n");
        return;
    }
    
    int id_cliente, id_servico;
    
    listarClientes();
    printf("\nID do cliente: ");
    scanf("%d", &id_cliente);
    
    listarServicos();
    printf("\nID do serviço: ");
    scanf("%d", &id_servico);
    
    Agendamento novo;
    novo.id = totalAgendamentos + 1;
    novo.id_cliente = id_cliente;
    novo.id_servico = id_servico;
    novo.realizado = 0;
    
    printf("Data (DD/MM/AAAA): ");
    scanf("%s", novo.data);
    printf("Hora (HH:MM): ");
    scanf("%s", novo.hora);
    
    agendamentos[totalAgendamentos++] = novo;
    printf("Agendamento realizado com sucesso! ID: %d\n", novo.id);
}

void listarAgendamentos() {
    printf("\n--- Lista de Agendamentos ---\n");
    for (int i = 0; i < totalAgendamentos; i++) {
        printf("ID: %d | Cliente: %s | Serviço: %s | Data: %s %s | %s\n", 
               agendamentos[i].id, 
               clientes[agendamentos[i].id_cliente - 1].nome,
               servicos[agendamentos[i].id_servico - 1].descricao,
               agendamentos[i].data, agendamentos[i].hora,
               agendamentos[i].realizado ? "Realizado" : "Pendente");
    }
}

void marcarComoRealizado() {
    int id;
    listarAgendamentos();
    printf("\nID do agendamento a marcar como realizado: ");
    scanf("%d", &id);
    
    if (id > 0 && id <= totalAgendamentos) {
        agendamentos[id-1].realizado = 1;
        printf("Agendamento marcado como realizado!\n");
    } else {
        printf("ID inválido!\n");
    }
}

void menuPrincipal() {
    int opcao;
    
    do {
        printf("\n--- Sistema de Barbearia ---\n");
        printf("1. Cadastrar Cliente\n");
        printf("2. Listar Clientes\n");
        printf("3. Cadastrar Serviço\n");
        printf("4. Listar Serviços\n");
        printf("5. Agendar Serviço\n");
        printf("6. Listar Agendamentos\n");
        printf("7. Marcar como Realizado\n");
        printf("0. Sair\n");
        printf("Opção: ");
        scanf("%d", &opcao);
        
        switch(opcao) {
            case 1: cadastrarCliente(); break;
            case 2: listarClientes(); break;
            case 3: cadastrarServico(); break;
            case 4: listarServicos(); break;
            case 5: agendarServico(); break;
            case 6: listarAgendamentos(); break;
            case 7: marcarComoRealizado(); break;
            case 0: printf("Saindo...\n"); break;
            default: printf("Opção inválida!\n");
        }
    } while (opcao != 0);
}

int main() {
    // Serviços padrão
    Servico s1 = {1, "Corte de Cabelo", 30.0, 30};
    Servico s2 = {2, "Barba", 20.0, 20};
    Servico s3 = {3, "Corte + Barba", 45.0, 50};
    
    servicos[totalServicos++] = s1;
    servicos[totalServicos++] = s2;
    servicos[totalServicos++] = s3;
    
    menuPrincipal();
    
    return 0;
}
