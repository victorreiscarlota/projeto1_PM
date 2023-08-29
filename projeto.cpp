#include <iostream>
#include <vector>

class Equipamento {
private:
    std::string codigo;
    std::string descricao;
    double valorDiario;

public:
    Equipamento(const std::string& codigo, const std::string& descricao, double valorDiario)
        : codigo(codigo), descricao(descricao), valorDiario(valorDiario) {}

    const std::string& getCodigo() const {
        return codigo;
    }

    const std::string& getDescricao() const {
        return descricao;
    }

    double getValorDiario() const {
        return valorDiario;
    }
};

class Cliente {
private:
    std::string nome;

public:
    Cliente(const std::string& nome)
        : nome(nome) {}

    const std::string& getNome() const {
        return nome;
    }
};

class Aluguel {
private:
    Cliente cliente;
    Equipamento equipamento;
    std::string dataInicio;
    std::string dataTermino;
    double valorTotal;

public:
    Aluguel(const Cliente& cliente, const Equipamento& equipamento, const std::string& dataInicio, const std::string& dataTermino)
        : cliente(cliente), equipamento(equipamento), dataInicio(dataInicio), dataTermino(dataTermino) {
        double numDias = 1.0; // Para Calcular o número de dias de aluguel
        valorTotal = numDias * equipamento.getValorDiario();
    }

    const Cliente& getCliente() const {
        return cliente;
    }

    const Equipamento& getEquipamento() const {
        return equipamento;
    }

    const std::string& getDataInicio() const {
        return dataInicio;
    }

    const std::string& getDataTermino() const {
        return dataTermino;
    }

    double getValorTotal() const {
        return valorTotal;
    }
};

class GerenciadorAlugueis {
private:
    std::vector<Aluguel> alugueis;

public:
    void registrarAluguel(const Cliente& cliente, const Equipamento& equipamento, const std::string& dataInicio, const std::string& dataTermino) {
        Aluguel novoAluguel(cliente, equipamento, dataInicio, dataTermino);
        alugueis.push_back(novoAluguel);
    }

    double calcularFaturamentoMensal(int mes, int ano) const {
        double faturamentoTotal = 0.0;
        for (const Aluguel& aluguel : alugueis) {
            // Verificação do mês e ano especificados do aluguel
            // e somar o valor ao faturamentoTotal
        }
        return faturamentoTotal;
    }

    std::vector<Aluguel> consultarAlugueisCliente(const Cliente& cliente) const {
        std::vector<Aluguel> alugueisCliente;
        for (const Aluguel& aluguel : alugueis) {
            if (aluguel.getCliente().getNome() == cliente.getNome()) {
                alugueisCliente.push_back(aluguel);
            }
        }
        return alugueisCliente;
    }
};

// Função que consulta os alugueis de um cliente especifico 
void consultaCliente(const GerenciadorAlugueis& gerenciador, const Cliente& cliente) {
    std::vector<Aluguel> alugueisCliente = gerenciador.consultarAlugueisCliente(cliente);

    std::cout << "Aluguéis do cliente " << cliente.getNome() << ":" << std::endl;
    for (const Aluguel& aluguel : alugueisCliente) {
        std::cout << "Equipamento: " << aluguel.getEquipamento().getDescricao()
                << " | Data Início: " << aluguel.getDataInicio()
                << " | Data Término: " << aluguel.getDataTermino()
                << " | Valor Total: " << aluguel.getValorTotal() << std::endl;
    }
}

// metodo que gera relatório mensal
void relatorioMensal(const GerenciadorAlugueis& gerenciador, int mes, int ano) {
    double faturamentoMensal = gerenciador.calcularFaturamentoMensal(mes, ano);

    std::cout << "Relatório Mensal - " << mes << "/" << ano << ":" << std::endl;
    std::cout << "Faturamento Total: " << faturamentoMensal << std::endl;
}

int main() {
    Equipamento equipamento1("E1", "Escavadeira", 200.0);
    Equipamento equipamento2("E2", "Betoneira", 150.0);

    Cliente cliente1("Cliente A");
    Cliente cliente2("Cliente B");

    GerenciadorAlugueis gerenciador;

    gerenciador.registrarAluguel(cliente1, equipamento1, "2023-08-01", "2023-08-05");
    gerenciador.registrarAluguel(cliente2, equipamento2, "2023-08-03", "2023-08-07");

    consultaCliente(gerenciador, cliente1);
    consultaCliente(gerenciador, cliente2);

    relatorioMensal(gerenciador, 8, 2023);

    return 0;
}
