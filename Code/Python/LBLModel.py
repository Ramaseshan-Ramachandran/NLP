#I want to write a log-bilinear class that uses distributed representations of words to predict the next word in a sequence.
import numpy as np
import torch
import torch.nn as nn

class LogBilinearModel:
    def __init__(self, vocab_size, embedding_dim, hidden_dim, output_dim, n_layers, dropout, pad_idx):
        self.vocab_size = vocab_size
        self.embedding_dim = embedding_dim
        self.hidden_dim = hidden_dim
        self.output_dim = output_dim
        self.n_layers = n_layers
        self.dropout = dropout
        self.pad_idx = pad_idx
        
        self.embedding = nn.Embedding(vocab_size, embedding_dim, padding_idx=pad_idx)
        self.rnn = nn.LSTM(embedding_dim, hidden_dim, n_layers, dropout=dropout, batch_first=True)
        self.fc = nn.Linear(hidden_dim, output_dim)
        self.softmax = nn.LogSoftmax(dim=1)
        
    def predict(self,context):
        embedded = self.embedding(context)
        packed = nn.utils.rnn.pack_padded_sequence(embedded, context.size(0), batch_first=True)
        hiddens, _ = self.rnn(packed)
        hiddens, _ = nn.utils.rnn.pad_packed_sequence(hiddens, batch_first=True)
        output = self.fc(hiddens)
        return output
    
    def train(self,corpus):
        loss_function = nn.NLLLoss()
        optimizer = torch.optim.Adam(self.parameters(), lr=0.001)
        for epoch in range(1000):
            total_loss = 0
            for context, target in corpus:
                output = self.predict(context)
                loss = loss_function(output, target)
                optimizer.zero_grad()
                loss.backward()
                optimizer.step()
                total_loss += loss.item()
            print(f'Epoch: {epoch}, Loss: {total_loss}')
    
    def read_corpus(self,corpus_folder):
        with open(corpus_folder) as f:
            for line in f:
                context, target = line.strip().split('\t')
                context = torch.tensor(context.split())
                target = torch.tensor(target.split())
                yield context, target

if __name__ == "main":
    model = LogBilinearModel(vocab_size=10000, embedding_dim=100, hidden_dim=100, output_dim=100, n_layers=1, dropout=0.5, pad_idx=0)
    model.train(model.read_corpus('data/train.txt'))        
    model.predict()