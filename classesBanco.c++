
#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Conta {
private:
    int numeroConta;
    string nomeTitular;
    float saldo;
public:
    Conta(int numeroConta, string nomeTitular, float saldo) : numeroConta(numeroConta), nomeTitular(nomeTitular), saldo(saldo) {}
    int getNumeroConta() const {
        return numeroConta;
    }
    void setSaldo(float saldo) {
        this->saldo = saldo;
    }
    float getSaldo() const {
        return saldo;
    }
    void setNomeTitular(string nomeTitular) {
        this->nomeTitular = nomeTitular;
    }
    string getNomeTitular() const   {
        return nomeTitular;
    }
    void emitirExtrato() const {
        cout << "Titular: " << getNomeTitular() << endl;
        cout << "Número da conta: " << getNumeroConta() << endl;
        cout << "Saldo: " << getSaldo() << endl;
    }
};

class AbrirConta {
private:
    int numeroConta;
    string nomeTitular;
public:
    void solicitarDados() {
        cout << "Informe o número da conta: ";
        cin >> numeroConta;
        cout << "Informe o nome do titular da conta: ";
        cin >> nomeTitular;
    }
    void abrir(vector<Conta>& contas) {
        bool contaExiste = false;
        for (const auto& conta : contas) {
            if (conta.getNumeroConta() == numeroConta) {
                cout << "Erro: conta já existente." << endl;
                contaExiste = true;
                break;
            }
        }
        if (!contaExiste) {
            Conta novaConta(numeroConta, nomeTitular, 0);
            contas.insert(contas.end(), novaConta);
            cout << "Conta " << numeroConta << " aberta para o titular " << nomeTitular << "." << endl;
        }
    }
};

class DepositarNaConta {
private:
    float valor;
    int numeroConta;
public:
    void solicitarDados() {
        cout << "Informe o valor a ser depositado: ";
        cin >> valor;
        cout << "Informe o número da conta de destino: ";
        cin >> numeroConta;
    }
    void depositar(vector<Conta>& contas) {
        for (auto& conta : contas) {
            if (conta.getNumeroConta() == numeroConta) {
                float saldoAtual = conta.getSaldo();
                conta.setSaldo(saldoAtual + valor);
                cout << "Depósito realizado na conta " << numeroConta << "." << endl;
                cout << "Novo saldo: " << conta.getSaldo() << endl;
                return;
            }
        }
        cout << "Conta não encontrada." << endl;
    }
};



class TransferirEntreContas {
private:
    float valor;
    int numeroContaOrigem;
    int numeroContaDestino;
public:
    void solicitarDados() {
        cout << "Informe o valor a ser transferido: ";
        cin >> valor;
        cout << "Informe o número da conta de origem: ";
        cin >> numeroContaOrigem;
        cout << "Informe o número da conta de destino: ";
        cin >> numeroContaDestino;
    }
    void transferir(vector<Conta>& contas) {
        Conta* contaOrigem = nullptr;
        Conta* contaDestino = nullptr;

        for (auto& conta : contas) {
            if (conta.getNumeroConta() == numeroContaOrigem) {
                contaOrigem = &conta;
            } else if (conta.getNumeroConta() == numeroContaDestino) {
                contaDestino = &conta;
            }

            if (contaOrigem != nullptr && contaDestino != nullptr) {
                break;
            }
        }

        if (contaOrigem == nullptr) {
            cout << "Conta de origem não encontrada." << endl;
        } else if (contaDestino == nullptr) {
            cout << "Conta de destino não encontrada." << endl;
        } else {
            float saldoOrigem = contaOrigem->getSaldo();
            if (valor > saldoOrigem) {
                cout << "Saldo insuficiente na conta de origem." << endl;
            } else {
                contaOrigem->setSaldo(saldoOrigem - valor);
                float saldoDestino = contaDestino->getSaldo();
                contaDestino->setSaldo(saldoDestino + valor);
                cout << "Transferência realizada." << endl;
                cout << "Novo saldo da conta de origem: " << contaOrigem->getSaldo() << endl;
                cout << "Novo saldo da conta de destino: " << contaDestino->getSaldo() << endl;
            }
        }
    }
};
class SacarDaConta {
private:
    float valor;
    int numeroConta;
public:
    void solicitarDados() {
        cout << "Informe o valor a ser sacado: ";
        cin >> valor;
        cout << "Informe o número da conta de origem: ";
        cin >> numeroConta;
    }
    void sacar(vector<Conta>& contas) {
        for (auto& conta : contas) {
            if (conta.getNumeroConta() == numeroConta) {
                float saldoAtual = conta.getSaldo();
                if (valor > saldoAtual) {
                    cout << "Saldo insuficiente." << endl;
                    return;
                }

                conta.setSaldo(saldoAtual - valor);
            cout << "Saque realizado na conta " << numeroConta << "." << endl;
            cout << "Novo saldo: " << conta.getSaldo() << endl;
            return;
        }
    }
    cout << "Conta não encontrada." << endl;
}
};

int main() {
    vector<Conta> contas;
    int opcao = 0;
    while (opcao != 6) {
        cout << endl;
        cout << "Selecione uma opção:" << endl;
        cout << "1 - Abrir conta" << endl;
        cout << "2 - Depositar na conta" << endl;
        cout << "3 - Sacar da conta" << endl;
        cout << "4 - Emitir extrato da conta" << endl;
        cout << "5 - Transferencia entre contas" << endl;
        cout << "6 - Sair" << endl;
        cin >> opcao;
        switch (opcao) {
            case 1: {
                AbrirConta abrirConta;
                abrirConta.solicitarDados();
                abrirConta.abrir(contas);
                break;
            }
            case 2: {
                DepositarNaConta depositarNaConta;
                depositarNaConta.solicitarDados();
                depositarNaConta.depositar(contas);
                break;
            }
            case 3: {
                SacarDaConta sacarDaConta;
                sacarDaConta.solicitarDados();
                sacarDaConta.sacar(contas);
                break;
            }
            case 4: {
                int numeroConta;
                cout << "Informe o número da conta: ";
                cin >> numeroConta;
                for (auto& conta : contas) {
                    if (conta.getNumeroConta() == numeroConta) {
                        conta.emitirExtrato();
                        break;
                    }
                }
                break;
            }
                case 5: {
               TransferirEntreContas transferirEntreContas;
               transferirEntreContas.solicitarDados();
               transferirEntreContas.transferir(contas);
               break;

               }
                
            case 6:
              cout<<"Finalizado."<<endl;
            break;

            default:
                cout << "Opção inválida." << endl;
                break;
        }
    }
    return 0;
}
