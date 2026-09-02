# SISTRI-FOME
> **Sistema de Triagem e Direcionamento de Assistência Alimentar Microrregional**  
> Relatório Final – Disciplina de Programação I

---

## 1. Identificação da Equipe

* **Integrante 1:** Pedro H. Santos Da Cruz
* **Integrante 2:** Iury Almeida da Cunha
* **Coordenador:** Iury Almeida da Cunha
* **Disciplina:** Programação I – M01
* **Professor:** Flávio Izo
* **Instituição:** IFES – Campus Cachoeiro de Itapemirim
* **Data de entrega:** 25/06/2026

---

## 2. ODS Relacionada

**ODS 2 – Fome Zero e Agricultura Sustentável**

A proposta se alinha ao Objetivo de Desenvolvimento Sustentável nº 2 da ONU, que busca erradicar a fome e alcançar a segurança alimentar. O **SISTRI-FOME** atua diretamente na identificação e triagem de pessoas em situação de insegurança alimentar na microrregião do Sul do Espírito Santo, acelerando o acesso à assistência adequada.

---

## 3. Descrição do Problema

A fome afeta moradores de rua e famílias de baixa renda em centros urbanos, periferias e áreas rurais da microrregião de Cachoeiro de Itapemirim (que abrange também Apiacá, Atílio Vivacqua, Castelo, Mimoso do Sul, Muqui e Vargem Alta). A lentidão e a falta de padronização nos processos manuais de triagem da assistência social atrasam a distribuição de alimentos para quem está em situação de vulnerabilidade extrema, gerando ineficiência no uso dos recursos públicos e atraso no atendimento emergencial.

---

## 4. Solução Proposta

O **SISTRI-FOME** é um sistema informatizado de triagem socioeconômica operado por assistentes sociais em postos de atendimento. 

Por meio de um questionário objetivo inserido no sistema, a ferramenta calcula automaticamente o nível de insegurança alimentar do cidadão – com base em cinco critérios ponderados (alimentação diária, condição de moradia, fonte de renda, dependentes vulneráveis e histórico de falta de alimento) – e gera encaminhamento imediato para o recurso correto:

* **Cozinha Comunitária e Abrigo:** Insegurança extrema (pontuação $\ge 14$).
* **Entrega de Cestas Básicas:** Insegurança moderada (pontuação $\ge 7$).
* **Inclusão em Programas Sociais de Renda:** Insegurança leve (pontuação $< 7$).

Isso elimina a subjetividade das triagens manuais e reduz o tempo de resposta do atendimento emergencial.

---

## 5. Recursos Implementados

A tabela abaixo descreve como cada recurso obrigatório da disciplina foi aplicado no sistema:

| Recurso | Como foi implementado |
| :--- | :--- |
| **Modularização** | O programa é dividido em seis funções independentes: `menu()`, `cadastrarUsuario()`, `realizarTriagem()`, `pesquisarBeneficiario()`, `salvarDados()` e `carregarDados()`. A função `main()` apenas coordena as chamadas via `switch`. |
| **Vetores / Structs** | Os dados são armazenados em um vetor de structs `Cidadao[MAX_CIDADAOS]` (máx. 100 registros), onde cada posição guarda nome, CPF, cidade, bairro e resultado da triagem. |
| **Decisão (if / switch)** | O `switch` avalia a opção do menu. Na triagem, uma cadeia `if / else if / else` compara a pontuação acumulada (0–20) e define o encaminhamento automático em três níveis de insegurança alimentar. |
| **Repetição (for / do-while)** | O laço `do-while` mantém o menu ativo até o usuário sair. Laços `for` percorrem o vetor nas funções de triagem, pesquisa, `salvarDados()` e `carregarDados()`. |
| **Armazenamento (arquivo)** | A função `salvarDados()` grava todos os registros em `dados.txt` no modo escrita (`"w"`), iniciando pelo total de cadastros para facilitar a releitura. |
| **Leitura (arquivo)** | A função `carregarDados()` é chamada na inicialização e reconstrói o vetor a partir de `dados.txt` usando `fscanf` e `fgets`, restaurando atendimentos anteriores. |
| **Pesquisa** | `pesquisarBeneficiario()` realiza busca linear por CPF no vetor em memória, exibindo todos os dados do cidadão localizado, incluindo o resultado da triagem. |

---

## 6. Instruções para Compilar e Executar

### Pré-requisito
Compilador **GCC** instalado (padrão em distribuições Linux; disponível no Windows via MinGW ou WSL).

### Passo 1 – Compilar
```bash
gcc sistri-fome.c -o sistri