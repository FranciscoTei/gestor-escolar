#ifndef PROFESSOR_H
#define PROFESSOR_H

void menuProfessor(int usuario_id);
void gerenciarTurmas(int usuario_id);
void gerenciarHorarios(int usuario_id);
void configuracoesProfessor(int usuario_id);

void listarTurmas(int usuario_id);
void menuTurma(int turma_id);
void gerenciarAlunos(int turma_id);
void gerenciarAtividades(int turma_id);
void gerenciarAvisos(int turma_id);
void gerenciarForum(int turma_id);

void listarAlunos(int turma_id);
void cadastrarNotas(int turma_id);
void verNotas(int turma_id);

void listarAtividades(int turma_id);
void abrirAtividade(int atividade_id);
void criarAtividade(int turma_id);

void listarAvisos(int turma_id);
void abrirAviso(int aviso_id);
void criarAviso(int turma_id);

void listarTopicos(int turma_id);
void abrirTopico(int topico_id);
void criarTopico(int turma_id);

#endif // PROFESSOR_H
