import { Injectable } from '@angular/core';

@Injectable({
  providedIn: 'root'
})
export class SignInService {
  isLoggedIn: boolean = false;
  user = {
    email: '',
    password: ''
  };

  constructor() { }

  getIsLoggedIn(): boolean {
    return this.isLoggedIn;
  }

  setIsLoggedIn(isLoggedIn: boolean): void {
    this.isLoggedIn = isLoggedIn;
  }

  setUser(user) {
    this.user = user;
  }

  getUser() {
    return this.user;
  }
}
