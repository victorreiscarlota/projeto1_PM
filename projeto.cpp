#include <iostream>
#include <vector>
#include <string>
#include <chrono>

class Equipamento
{
public:
    Equipamento(std::string codigo, std::string descricao) : codigo(codigo), descricao(descricao) {}

    std::string codigo;
    std::string descricao;
};

class Aluguel
{
public:
    Aluguel(class Cliente *cliente, class Equipamento *equipamento, double valor_diario, std::chrono::system_clock::time_point data_inicio, std::chrono::system_clock::time_point data_termino)
        : cliente(cliente), equipamento(equipamento), valor_diario(valor_diario), data_inicio(data_inicio), data_termino(data_termino) {}

    double valor_total()
    {
        std::chrono::duration<double> duration = data_termino - data_inicio;
        int dias = std::chrono::duration_cast<std::chrono::hours>(duration).count() / 24;
        return valor_diario * dias;
    }

    class Cliente *cliente;
    class Equipamento *equipamento;
    double valor_diario;
    std::chrono::system_clock::time_point data_inicio;
    std::chrono::system_clock::time_point data_termino;
};

class Cliente
{
public:
    Cliente(std::string nome) : nome(nome) {}

    std::string nome;
};

int main()
{
    // Criação de alguns equipamentos
    Equipamento equipamento1("E001", "Furadeira");
    Equipamento equipamento2("E002", "Martelo");

    // Criação de um cliente
    Cliente cliente1("João");

    // Criação de um novo aluguel
    auto data_inicio = std::chrono::system_clock::now();
    auto data_termino = data_inicio + std::chrono::hours(24 * 103); // 103 dias
    Aluguel novo_aluguel(&cliente1, &equipamento1, 50.00, data_inicio, data_termino);

    // Cálculo do valor total do aluguel
    double valor_total = novo_aluguel.valor_total();
    std::cout << "Valor total do aluguel: R$" << valor_total << std::endl;

    // Armazenamento dos aluguéis
    std::vector<Aluguel> alugueis_passados;

    // Adição do aluguel à lista de aluguéis passados
    alugueis_passados.push_back(novo_aluguel);

    // Consulta de aluguéis por cliente
    auto consulta_cliente = [&alugueis_passados](std::string nome_cliente)
    {
        for (const auto &aluguel : alugueis_passados)
        {
            if (aluguel.cliente->nome == nome_cliente)
            {
                std::cout << "Cliente: " << aluguel.cliente->nome
                        << ", Equipamento: " << aluguel.equipamento->descricao
                        << ", Valor: R$" << aluguel.valor_diario << " por dia" << std::endl;
            }
        }
    };

    // Chamada da função de consulta
    consulta_cliente("João");

    // Relatório mensal
    auto relatorio_mensal = [&alugueis_passados](int mes, int ano)
    {
        double faturamento_total = 0.0;
        for (const auto &aluguel : alugueis_passados)
        {
            std::time_t start_time = std::chrono::system_clock::to_time_t(aluguel.data_inicio);
            struct std::tm *timeinfo = std::localtime(&start_time);
            int aluguel_mes = timeinfo->tm_mon + 1; // tm_mon is 0-indexed
            int aluguel_ano = timeinfo->tm_year + 1900;

            if (aluguel_mes == mes && aluguel_ano == ano)
            {
                faturamento_total += aluguel.valor_total();
            }
        }
        std::cout << "Relatório do mês " << mes << "/" << ano << std::endl;
        std::cout << "Faturamento total: R$" << faturamento_total << std::endl;
    };

    // Chamada do relatório mensal
    relatorio_mensal(6, 2023);

    return 0;
}
