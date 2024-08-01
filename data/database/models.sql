
CREATE TABLE IF NOT EXISTS usuario (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    nome TEXT NOT NULL,
    email TEXT UNIQUE NOT NULL,
    senha TEXT NOT NULL,
    status TEXT NOT NULL CHECK(status IN ('aluno', 'professor', 'monitor', 'coordenador', 'administrador'))
);


CREATE TABLE IF NOT EXISTS usuario_endereco (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    cidade TEXT NOT NULL,
    bairro TEXT NOT NULL,
    rua TEXT NOT NULL,
    cep TEXT NOT NULL,
    usuario_id INTEGER NOT NULL,
    FOREIGN KEY (usuario_id) REFERENCES usuario(id)
);


CREATE TABLE IF NOT EXISTS turmas (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    nome TEXT NOT NULL,
    sigla TEXT NOT NULL,
    codigo TEXT NOT NULL,
    carga_horaria INTEGER NOT NULL
);


CREATE TABLE IF NOT EXISTS horario (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    nome TEXT NOT NULL,
    sigla TEXT NOT NULL,
    codigo TEXT NOT NULL,
    dia_semana TEXT NOT NULL CHECK(dia_semana IN ('segunda', 'terça', 'quarta', 'quinta', 'sexta', 'sábado', 'domingo')),
    horario_inicio TEXT NOT NULL
);



CREATE TABLE IF NOT EXISTS turmas_disciplinas (
    turma_id INTEGER NOT NULL,
    disciplina_id INTEGER NOT NULL,
    PRIMARY KEY (turma_id, disciplina_id),
    FOREIGN KEY (turma_id) REFERENCES turmas(id),
    FOREIGN KEY (disciplina_id) REFERENCES disciplinas(id)
);


CREATE TABLE IF NOT EXISTS forums (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    titulo TEXT NOT NULL,
    descricao TEXT,
    turma_id INTEGER NOT NULL,
    professor_id INTEGER NOT NULL,
    data_criacao DATETIME DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (turma_id) REFERENCES turmas(id),
    FOREIGN KEY (professor_id) REFERENCES usuario(id)
);


CREATE TABLE IF NOT EXISTS comentarios_forum (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    forum_id INTEGER NOT NULL,
    usuario_id INTEGER NOT NULL,
    comentario TEXT NOT NULL,
    data_comentario DATETIME DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (forum_id) REFERENCES forums(id),
    FOREIGN KEY (usuario_id) REFERENCES usuario(id)
);


CREATE TABLE IF NOT EXISTS atividades (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    titulo TEXT NOT NULL,
    descricao TEXT,
    turma_id INTEGER NOT NULL,
    data_entrega DATE,
    FOREIGN KEY (turma_id) REFERENCES turmas(id)
);


CREATE TABLE IF NOT EXISTS avisos (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    titulo TEXT NOT NULL,
    mensagem TEXT NOT NULL,
    turma_id INTEGER NOT NULL,
    data_aviso DATETIME DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (turma_id) REFERENCES turmas(id)
);


CREATE TABLE IF NOT EXISTS turmas_usuarios (
    turma_id INTEGER NOT NULL,
    usuario_id INTEGER NOT NULL,
    PRIMARY KEY (turma_id, usuario_id),
    FOREIGN KEY (turma_id) REFERENCES turmas(id),
    FOREIGN KEY (usuario_id) REFERENCES usuario(id)
);


CREATE TABLE IF NOT EXISTS disciplinas_professores (
    disciplina_id INTEGER NOT NULL,
    professor_id INTEGER NOT NULL,
    PRIMARY KEY (disciplina_id, professor_id),
    FOREIGN KEY (disciplina_id) REFERENCES disciplinas(id),
    FOREIGN KEY (professor_id) REFERENCES usuario(id)
);