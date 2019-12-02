import { Component, OnInit } from '@angular/core';
import { Router } from '@angular/router';
import { MatDialog } from '@angular/material';
import { SignInService } from '../sign-in.service';
import { HttpClient, HttpHeaders } from '@angular/common/http';
import { take } from 'rxjs/operators';

@Component({
  selector: 'app-sign-in',
  templateUrl: './sign-in.component.html',
  styleUrls: ['./sign-in.component.css']
})
export class SignInComponent implements OnInit {
  username: string;
  password: string;
  httpOptions = new HttpHeaders({
    user: '',
    password: ''
  })
  constructor(private http: HttpClient, private signInService: SignInService, private router: Router) { }
  ngOnInit() {
  }
  login() : void {
    this.httpOptions.set('user', this.username);
    this.httpOptions.set('password', this.password);
    this.http.post('signInLink', {}, {headers: this.httpOptions}).pipe(take(1)).subscribe(res => {
      if(res == "invalid"){
        alert("Invalid username/password");
      } else {
        this.signInService.setUser(res);
        this.signInService.setIsLoggedIn(true);
        this.router.navigate(["authhome"]);
      }
    })
  }
   register() : void {
     this.router.navigate(["reg"]);
   }
 }

