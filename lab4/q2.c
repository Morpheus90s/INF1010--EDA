void intervalo(t_no *arv, int lim_inf, int lim_sup) {
    
    if (arv == NULL) {
        return;
    }
    int i;
    for (i = 0; i < arv->ndesc; i++) {
        intervalo(arv->ramo[i], lim_inf, lim_sup);
        if (arv->chave[i] > lim_inf && arv->chave[i] < lim_sup) {
            printf("%d\n", arv->chave[i]);
        }
    }

    intervalo(arv->ramo[i], lim_inf, lim_sup);
}