-- data/database/insert_data.sql

-- Inserir dados na tabela usuario
INSERT INTO usuario (nome, email, senha, status) VALUES
('Alice', 'alice@example.com', 'senha123', 'aluno'),
('Bob', 'bob@example.com', 'senha456', 'professor');

-- Inserir dados na tabela usuario_endereco
INSERT INTO usuario_endereco (cidade, bairro, rua, cep, usuario_id) VALUES
('Cidade A', 'Bairro A', 'Rua A', '12345-678', 1),
('Cidade B', 'Bairro B', 'Rua B', '23456-789', 2);

-- Inserir dados na tabela turmas
INSERT INTO turmas (nome, sigla, codigo, carga_horaria) VALUES
('Turma 1', 'T1', 'C001', 60),
('Turma 2', 'T2', 'C002', 45);

-- Inserir dados na tabela horario
INSERT INTO horario (nome, sigla, codigo, dia_semana, horario_inicio) VALUES
('Matéria A', 'MA', 'H001', 'segunda', '08:00'),
('Matéria B', 'MB', 'H002', 'quarta', '10:00');

-- Inserir dados na tabela turmas_disciplinas
INSERT INTO turmas_disciplinas (turma_id, disciplina_id) VALUES
(1, 1),
(2, 2);

-- Inserir dados na tabela forums
INSERT INTO forums (titulo, descricao, turma_id, professor_id) VALUES
('Forum 1', 'Descrição do fórum 1', 1, 2),
('Forum 2', 'Descrição do fórum 2', 2, 2);

-- Inserir dados na tabela comentarios_forum
INSERT INTO comentarios_forum (forum_id, usuario_id, comentario, data_comentario) VALUES
(1, 1, 'Comentário 1', '2024-07-31 10:00:00'),
(2, 2, 'Comentário 2', '2024-07-31 11:00:00');

-- Inserir dados na tabela atividades
INSERT INTO atividades (titulo, descricao, turma_id, data_entrega) VALUES
('Atividade 1', 'Descrição da atividade 1', 1, '2024-08-15'),
('Atividade 2', 'Descrição da atividade 2', 2, '2024-08-20');

-- Inserir dados na tabela avisos
INSERT INTO avisos (titulo, mensagem, turma_id, data_aviso) VALUES
('Aviso 1', 'Mensagem do aviso 1', 1, '2024-07-31 09:00:00'),
('Aviso 2', 'Mensagem do aviso 2', 2, '2024-07-31 10:00:00');

-- Inserir dados na tabela turmas_usuari
