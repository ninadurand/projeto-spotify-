#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <dirent.h>
#include <time.h>

typedef struct Musica {
    char titulo[50];
    char artista[50];
    char album[50];
    int minutos;
    int segundos;
    struct Musica *prox;
    struct Musica *ant;
} Musica;

typedef struct {
    Musica *inicio;
} ListaReproducao;

Musica* criarMusica(char titulo[], char artista[], char album[], int minutos, int segundos);
ListaReproducao* criarLista();
void adicionarMusica(ListaReproducao *lista, char titulo[], char artista[], char album[], int minutos, int segundos);
void visualizarMusicas(ListaReproducao *lista);
void removerMusica(ListaReproducao *lista);
void limparLista(ListaReproducao *lista);
int contarMusicas(ListaReproducao *lista);
void ordenarPorTitulo(ListaReproducao *lista);
void salvarLista(ListaReproducao *lista);
void carregarLista(ListaReproducao *lista);
void tocarSequencial(ListaReproducao *lista);
void tocarAleatorio(ListaReproducao *lista);
void pesquisarMusica(ListaReproducao *lista);
void exibirMenu(ListaReproducao *lista);
void dadosMusica(ListaReproducao *lista);

int main() {
    setlocale(LC_ALL, "");
    ListaReproducao *minhaLista = criarLista();
    exibirMenu(minhaLista);
    limparLista(minhaLista);
    free(minhaLista);
    return 0;
}

void exibirMenu(ListaReproducao *lista) {
    int opcao;
    printf("\n=========================================\n");
    printf("          Minha Lista de Musicas app     \n");
    printf("                 v0.3                    \n");
    printf("=========================================\n");

    do {
        printf("\nMenu de Opções:\n");
        printf("1 - Adicionar Música\n");
        printf("2 - Remover Música\n");
        printf("3 - Visualizar Lista\n");
        printf("4 - Limpar Lista\n");
        printf("5 - Ordenar Lista por Título (Alfabética)\n");
        printf("6 - Tocar Lista (Sequencial)\n");
        printf("7 - Tocar em Ordem Aleatória\n");
        printf("8 - Pesquisar Música por Título\n");
        printf("9 - Total de Músicas\n");
        printf("10 - Salvar Lista\n");
        printf("11 - Carregar Lista Salva\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                dadosMusica(lista);
                break;
            }
            case 2:
                removerMusica(lista);
                break;
            case 3:
                visualizarMusicas(lista);
                break;
            case 4:
                limparLista(lista);
                printf("Lista de reprodução limpa.\n");
                break;
            case 5:
                ordenarPorTitulo(lista);
                break;
            case 6:
                tocarSequencial(lista);
                break;
            case 7:
                tocarAleatorio(lista);
                break;
            case 8:
                pesquisarMusica(lista);
                break;
            case 9:
                printf("Total de músicas na lista: %d\n", contarMusicas(lista));
                break;
            case 10:
                salvarLista(lista);
                break;
            case 11:
                carregarLista(lista);
                break;
            case 0:
                printf("Saindo do programa...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 0);
}

Musica* criarMusica(char titulo[], char artista[], char album[], int minutos, int segundos) {
    Musica *novaMusica = (Musica *)malloc(sizeof(Musica));
    strcpy(novaMusica->titulo, titulo);
    strcpy(novaMusica->artista, artista);
    strcpy(novaMusica->album, album);
    novaMusica->minutos = minutos;
    novaMusica->segundos = segundos;
    novaMusica->prox = novaMusica->ant = novaMusica;
    return novaMusica;
}

ListaReproducao* criarLista() {
    ListaReproducao *lista = (ListaReproducao *)malloc(sizeof(ListaReproducao));
    lista->inicio = NULL;
    return lista;
}

void adicionarMusica(ListaReproducao *lista, char titulo[], char artista[], char album[], int minutos, int segundos) {
    Musica *novaMusica = criarMusica(titulo, artista, album, minutos, segundos);
    if (lista->inicio == NULL) {
        lista->inicio = novaMusica;
    } else {
        Musica *ultima = lista->inicio->ant;
        ultima->prox = novaMusica;
        novaMusica->ant = ultima;
        novaMusica->prox = lista->inicio;
        lista->inicio->ant = novaMusica;
    }
    printf("Música '%s' adicionada com sucesso!\n", titulo);
}

void visualizarMusicas(ListaReproducao *lista) {
    if (lista->inicio == NULL) {
        printf("A lista de reprodução está vazia.\n");
        return;
    }
    Musica *atual = lista->inicio;
    do {
        printf("Título: %s, Artista: %s, Álbum: %s, Duração: %d:%02d\n",
               atual->titulo, atual->artista, atual->album, atual->minutos, atual->segundos);
        atual = atual->prox;
    } while (atual != lista->inicio);
}

void tocarSequencial(ListaReproducao *lista) {
    if (lista->inicio == NULL) {
        printf("A lista de reprodução está vazia. Não há músicas para tocar.\n");
        return;
    }

    Musica *atual = lista->inicio;
    do {
        printf("Tocando: %s - %s (%s) [%d:%02d]\n",
               atual->titulo, atual->artista, atual->album, atual->minutos, atual->segundos);
        atual = atual->prox;
    } while (atual != lista->inicio);
}

void tocarAleatorio(ListaReproducao *lista) {
    if (lista->inicio == NULL) {
        printf("A lista de reprodução está vazia. Não há músicas para tocar.\n");
        return;
    }

    int totalMusicas = contarMusicas(lista);
    int *indices = malloc(totalMusicas * sizeof(int));
    Musica *atual = lista->inicio;

    for (int i = 0; i < totalMusicas; i++) {
        indices[i] = i;
        atual = atual->prox;
    }

    srand(time(NULL));
    for (int i = totalMusicas - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = indices[i];
        indices[i] = indices[j];
        indices[j] = temp;
    }

    for (int i = 0; i < totalMusicas; i++) {
        atual = lista->inicio;
        for (int j = 0; j < indices[i]; j++) {
            atual = atual->prox;
        }
        printf("Tocando: %s - %s (%s) [%d:%02d]\n",
               atual->titulo, atual->artista, atual->album, atual->minutos, atual->segundos);
    }

    free(indices);
}

int contarMusicas(ListaReproducao *lista) {
    if (lista->inicio == NULL) {
        return 0;
    }
    int contador = 0;
    Musica *atual = lista->inicio;
    do {
        contador++;
        atual = atual->prox;
    } while (atual != lista->inicio);
    return contador;
}

void pesquisarMusica(ListaReproducao *lista) {
    if (lista->inicio == NULL) {
        printf("A lista de reprodução está vazia.\n");
        return;
    }

    char titulo[50];
    printf("Digite o título da música à pesquisar: ");
    scanf(" %[^\n]%*c", titulo);

    Musica *atual = lista->inicio;
    int encontrado = 0;
    do {
        if (strcasecmp(atual->titulo, titulo) == 0) {
            printf("Música encontrada: %s - %s (%s) [%d:%02d]\n",
                   atual->titulo, atual->artista, atual->album, atual->minutos, atual->segundos);
            encontrado = 1;
            break;
        }
        atual = atual->prox;
    } while (atual != lista->inicio);

    if (!encontrado) {
        printf("Música '%s' não encontrada na lista.\n", titulo);
    }
}

void carregarLista(ListaReproducao *lista) {
    DIR *dir;
    struct dirent *ent;
    char arquivos[100][60]; 
    int arquivoCount = 0;

    if ((dir = opendir(".")) != NULL) {
        printf("Listas disponíveis para carregar:\n");

        while ((ent = readdir(dir)) != NULL) {
            if (strstr(ent->d_name, ".txt")) {
                printf("%d - %s\n", arquivoCount + 1, ent->d_name);
                strncpy(arquivos[arquivoCount], ent->d_name, 60);
                arquivoCount++;
            }
        }
        closedir(dir);

        if (arquivoCount == 0) {
            printf("Nenhuma lista salva encontrada.\n");
            return;
        }

        int escolha;
        printf("Digite o número da lista que deseja carregar: ");
        scanf("%d", &escolha);

        if (escolha < 1 || escolha > arquivoCount) {
            printf("Opção inválida.\n");
            return;
        }

        char *nomeArquivo = arquivos[escolha - 1];
        FILE *arquivo = fopen(nomeArquivo, "r");
        if (arquivo == NULL) {
            printf("Erro ao abrir o arquivo para leitura.\n");
            return;
        }

        limparLista(lista);

        char titulo[50], artista[50], album[50];
        int minutos, segundos;

        while (fscanf(arquivo, " %[^\n]%*c", titulo) == 1) {
            fscanf(arquivo, " %[^\n]%*c", artista);
            fscanf(arquivo, " %[^\n]%*c", album);
            fscanf(arquivo, "%d %d%*c", &minutos, &segundos);
            adicionarMusica(lista, titulo, artista, album, minutos, segundos);
        }

        printf("Lista de músicas carregada de '%s'.\n", nomeArquivo);
        fclose(arquivo);
    } else {
        printf("Erro ao abrir o diretório.\n");
    }
}

void salvarLista(ListaReproducao *lista) {
    char nomeLista[50];
    printf("Digite o nome da lista para salvar (sem espaços): ");
    scanf("%s", nomeLista);

    char nomeArquivo[60];
    snprintf(nomeArquivo, sizeof(nomeArquivo), "%s.txt", nomeLista);

    FILE *arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    Musica *atual = lista->inicio;
    if (atual == NULL) {
        printf("A lista está vazia. Nada para salvar.\n");
        fclose(arquivo);
        return;
    }

    do {
        fprintf(arquivo, "%s\n%s\n%s\n%d %d\n", atual->titulo, atual->artista, atual->album, atual->minutos, atual->segundos);
        atual = atual->prox;
    } while (atual != lista->inicio);

    printf("Lista de músicas salva em '%s'.\n", nomeArquivo);
    fclose(arquivo);
}

void ordenarPorTitulo(ListaReproducao *lista) {
    if (lista->inicio == NULL){
    	printf("Lista vazia\n");
    	printf("\n");
		return;
	} 

    int trocado;
    do {
        trocado = 0;
        Musica *atual = lista->inicio;
        do {
            Musica *proximo = atual->prox;
            if (strcmp(atual->titulo, proximo->titulo) > 0) {
                char tempTitulo[50], tempArtista[50], tempAlbum[50];
                int tempMinutos, tempSegundos;

                strcpy(tempTitulo, atual->titulo);
                strcpy(tempArtista, atual->artista);
                strcpy(tempAlbum, atual->album);
                tempMinutos = atual->minutos;
                tempSegundos = atual->segundos;

                strcpy(atual->titulo, proximo->titulo);
                strcpy(atual->artista, proximo->artista);
                strcpy(atual->album, proximo->album);
                atual->minutos = proximo->minutos;
                atual->segundos = proximo->segundos;

                strcpy(proximo->titulo, tempTitulo);
                strcpy(proximo->artista, tempArtista);
                strcpy(proximo->album, tempAlbum);
                proximo->minutos = tempMinutos;
                proximo->segundos = tempSegundos;

                trocado = 1;
            }
            atual = atual->prox;
        } while (atual->prox != lista->inicio);
    } while (trocado);
    
    printf("LISTA ORGANIZADA - ALFABETICAMENTE\n");
}

void removerMusica(ListaReproducao *lista) {
    if (lista->inicio == NULL) {
        printf("A lista está vazia. Não há músicas para remover.\n");
        return;
    }

    printf("Músicas na lista:\n");
    visualizarMusicas(lista);

    char titulo[50];
    printf("Digite o título da música que deseja remover: ");
    scanf(" %[^\n]%*c", titulo);

    Musica *atual = lista->inicio;
    Musica *anterior = NULL;

    
    do {
        if (strcmp(atual->titulo, titulo) == 0) {  
            if (atual == lista->inicio && atual->prox == lista->inicio) { 
                lista->inicio = NULL;
            } else {
                if (atual == lista->inicio) { 
                    lista->inicio = atual->prox;
                }
                anterior = atual->ant;
                anterior->prox = atual->prox;
                atual->prox->ant = anterior;
            }
            free(atual);
            printf("Música '%s' removida com sucesso.\n", titulo);
            return;
        }
        atual = atual->prox;
    } while (atual != lista->inicio);

    printf("Música não encontrada na lista atual.\n");
}

void limparLista(ListaReproducao *lista) {
    if (lista->inicio == NULL) return;

    Musica *atual = lista->inicio;
    do {
        Musica *proxima = atual->prox;
        free(atual);
        atual = proxima;
    } while (atual != lista->inicio);

    lista->inicio = NULL;
}

void dadosMusica(ListaReproducao *lista){
	char titulo[50], artista[50], album[50];
    int minutos, segundos;
    printf("Digite o título: ");
    scanf(" %[^\n]%*c", titulo);
    printf("Digite o artista: ");
    scanf(" %[^\n]%*c", artista);
    printf("Digite o álbum: ");
    scanf(" %[^\n]%*c", album);
    printf("Digite a duração (minutos e segundos): ");
    scanf("%d %d", &minutos, &segundos);
    adicionarMusica(lista, titulo, artista, album, minutos, segundos);
}

